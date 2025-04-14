/*
 * RC522.c
 *
 *  Created on: Mar 23, 2022
 *      Author: LX
 */

#include "RC522.h"
#include "delay.h"
#include "spi.h"
#include "stdio.h"

#define RC522_RST_HIGH HAL_GPIO_WritePin(RC522_RST_GPIO_Port, RC522_RST_Pin, GPIO_PIN_SET);
#define RC522_RST_LOW HAL_GPIO_WritePin(RC522_RST_GPIO_Port, RC522_RST_Pin, GPIO_PIN_RESET);

#define RC522_ENABLE HAL_GPIO_WritePin(RC522_CS_GPIO_Port, RC522_CS_Pin, GPIO_PIN_RESET);
#define RC522_DISABLE HAL_GPIO_WritePin(RC522_CS_GPIO_Port, RC522_CS_Pin, GPIO_PIN_SET);

#define fac_us 100 // 时钟频率，单位MHZ

/*微秒级延时函数*/
/*void delay_us(uint32_t nus)
{
    uint32_t ticks;
    uint32_t told, tnow, tcnt = 0;
    uint32_t reload = SysTick->LOAD; // LOAD的值
    ticks = nus * fac_us;            // 需要的节拍数
    told = SysTick->VAL;             // 刚进入时的计数器值
    while (1)
    {
        tnow = SysTick->VAL;
        if (tnow != told)
        {
            if (tnow < told)
                tcnt += told - tnow; // 这里注意一下SYSTICK是一个递减的计数器就可以了.
            else
                tcnt += reload - tnow + told;
            told = tnow;
            if (tcnt >= ticks)
                break; // 时间超过/等于要延迟的时间,则退出.
        }
    }
}*/
int32_t SPI_WriteNBytes(SPI_HandleTypeDef *SPIx, uint8_t *p_TxData, uint32_t sendDataNum)
{
    /*uint8_t retry = 0; // 初始化重试计数器
    while (sendDataNum--) // 循环发送数据，直到sendDataNum为0
    {
        while ((SPIx->SR & SPI_FLAG_TXE) == 0) // 等待发送区空
        {
            retry++; // 增加重试计数
            if (retry > 20000) // 如果重试次数超过20000次，返回错误码-1
                return -1;
        }
        SPIx->DR = *p_TxData++; // 发送一个byte，并将指针移动到下一个byte
        retry = 0; // 重置重试计数器
        while ((SPIx->SR & SPI_FLAG_RXNE) == 0) // 等待接收完一个byte
        {
            SPIx->SR = SPIx->SR; // 读取SR寄存器以清除可能的错误标志
            retry++; // 增加重试计数
            if (retry > 20000) // 如果重试次数超过20000次，返回错误码-1
                return -1;
        }
        SPIx->DR; // 读取DR寄存器以清除接收到的数据
    }
    return 0; // 发送成功，返回0*/
    HAL_StatusTypeDef status;

    // 使用HAL库的SPI_Transmit函数发送数据
    status = HAL_SPI_Transmit(SPIx, p_TxData, sendDataNum, HAL_MAX_DELAY);
    if (status != HAL_OK)
    {
        // 如果传输失败，返回错误码-1
        return -1;
    }

    // 发送成功，返回0
    return 0;
}
int32_t SPI_ReadNBytes(SPI_TypeDef *SPIx, uint8_t *p_RxData, uint32_t readDataNum)
{
    uint8_t retry = 0;
    while (readDataNum--)
    {
        SPIx->DR = 0xFF;
        while (!(SPIx->SR & SPI_FLAG_TXE))
        {
            retry++;
            if (retry > 20000)
                return -1;
        }
        retry = 0;
        while (!(SPIx->SR & SPI_FLAG_RXNE))
        {
            retry++;
            if (retry > 20000)
                return -1;
        }
        *p_RxData++ = SPIx->DR;
    }
    return 0;
}
void RC522_Init(void)
{
    RC522_ENABLE;
    HAL_SPI_Transmit(&hspi2, (uint8_t *)0xaa, sizeof((uint8_t *)0xaa), 0xFF); // 启动传输
    RC522_DISABLE;

    HAL_Delay(50);
    PcdReset(); // 复位RC522读卡器
    HAL_Delay(10);
    PcdReset(); // 复位RC522读卡器
    HAL_Delay(10);
    PcdAntennaOff(); // 关闭天线发射
    HAL_Delay(10);
    PcdAntennaOn(); // 开启天线发射

    printf("RFID-MFRC522 初始化完成\r\nFindCard Starting ...\r\n"); // 测试引脚初始化完成
}

// 功    能：寻卡
// 参数说明: req_code[IN]:寻卡方式
//                 0x52 = 寻感应区内所有符合14443A标准的卡
//                 0x26 = 寻未进入休眠状态的卡
//           pTagType[OUT]：卡片类型代码
//                 0x4400 = Mifare_UltraLight
//                 0x0400 = Mifare_One(S50)
//                 0x0200 = Mifare_One(S70)
//                 0x0800 = Mifare_Pro(X)
//                 0x4403 = Mifare_DESFire
// 返    回: 成功返回MI_OK
char PcdRequest(unsigned char req_code, unsigned char *pTagType)
{
    char status;
    unsigned int unLen;
    unsigned char ucComMF522Buf[MAXRLEN];

    ClearBitMask(Status2Reg, 0x08);  // 清RC522寄存位
    WriteRawRC(BitFramingReg, 0x07); // 写RC623寄存器
    SetBitMask(TxControlReg, 0x03);  // 置RC522寄存位

    ucComMF522Buf[0] = req_code;

    status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 1, ucComMF522Buf, &unLen);
    if ((status == MI_OK) && (unLen == 0x10))
    {
        *pTagType = ucComMF522Buf[0];
        *(pTagType + 1) = ucComMF522Buf[1];
    }
    else
    {
        status = MI_ERR;
    }
    return status;
}
// 功    能：防冲撞
// 参数说明: pSnr[OUT]:卡片序列号，4字节
// 返    回: 成功返回MI_OK
char PcdAnticoll(unsigned char *pSnr)
{
    char status;
    unsigned char i, snr_check = 0;
    unsigned int unLen;
    unsigned char ucComMF522Buf[MAXRLEN];
    ClearBitMask(Status2Reg, 0x08);
    WriteRawRC(BitFramingReg, 0x00);
    ClearBitMask(CollReg, 0x80);
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;

    status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 2, ucComMF522Buf, &unLen);
    if (status == MI_OK)
    {
        for (i = 0; i < 4; i++)
        {
            *(pSnr + i) = ucComMF522Buf[i];
            snr_check ^= ucComMF522Buf[i];
        }
        if (snr_check != ucComMF522Buf[i])
        {
            status = MI_ERR;
        }
    }
    SetBitMask(CollReg, 0x80);
    return status;
}
// 功    能：选定卡片
// 参数说明: pSnr[IN]:卡片序列号，4字节
// 返    回: 成功返回MI_OK
char PcdSelect(unsigned char *pSnr)
{
    char status;
    unsigned char i;
    unsigned int unLen;
    unsigned char ucComMF522Buf[MAXRLEN];
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x70;
    ucComMF522Buf[6] = 0;
    for (i = 0; i < 4; i++)
    {
        ucComMF522Buf[i + 2] = *(pSnr + i);
        ucComMF522Buf[6] ^= *(pSnr + i);
    }
    CalulateCRC(ucComMF522Buf, 7, &ucComMF522Buf[7]);
    ClearBitMask(Status2Reg, 0x08);
    status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 9, ucComMF522Buf, &unLen);
    if ((status == MI_OK) && (unLen == 0x18))
    {
        status = MI_OK;
    }
    else
    {
        status = MI_ERR;
    }
    return status;
}
// 功    能：验证卡片密码
// 参数说明: auth_mode[IN]: 密码验证模式
//                  0x60 = 验证A密钥
//                  0x61 = 验证B密钥
//           addr[IN]：块地址
//           pKey[IN]：密码
//           pSnr[IN]：卡片序列号，4字节
// 返    回: 成功返回MI_OK
char PcdAuthState(unsigned char auth_mode, unsigned char addr, unsigned char *pKey, unsigned char *pSnr)
{
    char status;
    unsigned int unLen;
    unsigned char i, ucComMF522Buf[MAXRLEN];
    ucComMF522Buf[0] = auth_mode;
    ucComMF522Buf[1] = addr;
    for (i = 0; i < 6; i++)
    {
        ucComMF522Buf[i + 2] = *(pKey + i);
    }
    for (i = 0; i < 6; i++)
    {
        ucComMF522Buf[i + 8] = *(pSnr + i);
    }
    status = PcdComMF522(PCD_AUTHENT, ucComMF522Buf, 12, ucComMF522Buf, &unLen);
    if ((status != MI_OK) || (!(ReadRawRC(Status2Reg) & 0x08)))
    {
        status = MI_ERR;
    }
    return status;
}
// 功    能：读取M1卡一块数据
// 参数说明: addr[IN]：块地址
//           p [OUT]：读出的数据，16字节
// 返    回: 成功返回MI_OK
char PcdRead(unsigned char addr, unsigned char *pData)
{
    char status;
    unsigned int unLen;
    unsigned char i, ucComMF522Buf[MAXRLEN];
    ucComMF522Buf[0] = PICC_READ;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf, 2, &ucComMF522Buf[2]);

    status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);
    if ((status == MI_OK) && (unLen == 0x90))
    {
        for (i = 0; i < 16; i++)
        {
            *(pData + i) = ucComMF522Buf[i];
        }
    }
    else
    {
        status = MI_ERR;
    }
    return status;
}
// 功    能：写数据到M1卡一块
// 参数说明: addr[IN]：块地址
//           p [IN]：写入的数据，16字节
// 返    回: 成功返回MI_OK
char PcdWrite(unsigned char addr, unsigned char *pData)
{
    char status;
    unsigned int unLen;
    unsigned char i, ucComMF522Buf[MAXRLEN];
    ucComMF522Buf[0] = PICC_WRITE;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf, 2, &ucComMF522Buf[2]);
    status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);
    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {
        status = MI_ERR;
    }
    if (status == MI_OK)
    {
        for (i = 0; i < 16; i++)
        {
            ucComMF522Buf[i] = *(pData + i);
        }
        CalulateCRC(ucComMF522Buf, 16, &ucComMF522Buf[16]);

        status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 18, ucComMF522Buf, &unLen);
        if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {
            status = MI_ERR;
        }
    }
    return status;
}
// 功    能：扣款和充值
// 参数说明: dd_mode[IN]：命令字
//                0xC0 = 扣款
//                0xC1 = 充值
//           addr[IN]：钱包地址
//           pValue[IN]：4字节增(减)值，低位在前
// 返    回: 成功返回MI_OK
char PcdValue(unsigned char dd_mode, unsigned char addr, unsigned char *pValue)
{
    char status;
    unsigned int unLen;
    unsigned char i, ucComMF522Buf[MAXRLEN];
    ucComMF522Buf[0] = dd_mode;
    ucComMF522Buf[1] = addr;
    CalulateCRC(ucComMF522Buf, 2, &ucComMF522Buf[2]);
    status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);

    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {
        status = MI_ERR;
    }
    if (status == MI_OK)
    {
        for (i = 0; i < 16; i++)
        {
            ucComMF522Buf[i] = *(pValue + i);
        }
        CalulateCRC(ucComMF522Buf, 4, &ucComMF522Buf[4]);
        unLen = 0;
        status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 6, ucComMF522Buf, &unLen);
        if (status != MI_ERR)
        {
            status = MI_OK;
        }
    }
    if (status == MI_OK)
    {
        ucComMF522Buf[0] = PICC_TRANSFER;
        ucComMF522Buf[1] = addr;
        CalulateCRC(ucComMF522Buf, 2, &ucComMF522Buf[2]);

        status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);

        if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
        {
            status = MI_ERR;
        }
    }
    return status;
}
// 功    能：备份钱包
// 参数说明: sourceaddr[IN]：源地址
//           goaladdr[IN]：目标地址
// 返    回: 成功返回MI_OK
char PcdBakValue(unsigned char sourceaddr, unsigned char goaladdr)
{
    char status;
    unsigned int unLen;
    unsigned char ucComMF522Buf[MAXRLEN];
    ucComMF522Buf[0] = PICC_RESTORE;
    ucComMF522Buf[1] = sourceaddr;
    CalulateCRC(ucComMF522Buf, 2, &ucComMF522Buf[2]);
    status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);
    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {
        status = MI_ERR;
    }
    if (status == MI_OK)
    {
        ucComMF522Buf[0] = 0;
        ucComMF522Buf[1] = 0;
        ucComMF522Buf[2] = 0;
        ucComMF522Buf[3] = 0;
        CalulateCRC(ucComMF522Buf, 4, &ucComMF522Buf[4]);
        status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 6, ucComMF522Buf, &unLen);
        if (status != MI_ERR)
        {
            status = MI_OK;
        }
    }
    if (status != MI_OK)
    {
        return MI_ERR;
    }
    ucComMF522Buf[0] = PICC_TRANSFER;
    ucComMF522Buf[1] = goaladdr;
    CalulateCRC(ucComMF522Buf, 2, &ucComMF522Buf[2]);
    status = PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);
    if ((status != MI_OK) || (unLen != 4) || ((ucComMF522Buf[0] & 0x0F) != 0x0A))
    {
        status = MI_ERR;
    }
    return status;
}
// 功    能：命令卡片进入休眠状态
// 返    回: 成功返回MI_OK
char PcdHalt(void)
{
    // char status;
    unsigned int unLen;
    unsigned char ucComMF522Buf[MAXRLEN];

    ucComMF522Buf[0] = PICC_HALT;
    ucComMF522Buf[1] = 0;
    CalulateCRC(ucComMF522Buf, 2, &ucComMF522Buf[2]);

    PcdComMF522(PCD_TRANSCEIVE, ucComMF522Buf, 4, ucComMF522Buf, &unLen);

    return MI_OK;
}
// 用MF522计算CRC16函数
void CalulateCRC(unsigned char *pIndata, unsigned char len, unsigned char *pOutData)
{
    unsigned char i, n;
    ClearBitMask(DivIrqReg, 0x04);
    WriteRawRC(CommandReg, PCD_IDLE);
    SetBitMask(FIFOLevelReg, 0x80);
    for (i = 0; i < len; i++)
    {
        WriteRawRC(FIFODataReg, *(pIndata + i));
    }
    WriteRawRC(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do
    {
        n = ReadRawRC(DivIrqReg);
        i--;
    } while ((i != 0) && !(n & 0x04));
    pOutData[0] = ReadRawRC(CRCResultRegL);
    pOutData[1] = ReadRawRC(CRCResultRegM);
}
// 功    能：复位RC522
// 返    回: 成功返回MI_OK
char PcdReset(void)
{
    RC522_RST_HIGH;
    delay_us(10);
    RC522_RST_LOW;
    HAL_Delay(60);
    RC522_RST_HIGH;
    delay_us(500);
    WriteRawRC(CommandReg, PCD_RESETPHASE);
    HAL_Delay(2);

    WriteRawRC(ModeReg, 0x3D);
    WriteRawRC(TReloadRegL, 30);
    WriteRawRC(TReloadRegH, 0);
    WriteRawRC(TModeReg, 0x8D);
    WriteRawRC(TPrescalerReg, 0x3E);
    WriteRawRC(TxAutoReg, 0x40);

    ClearBitMask(TestPinEnReg, 0x80);
    WriteRawRC(TxAutoReg, 0x40);

    return MI_OK;
}
// 功    能：读RC632寄存器
// 参数说明：Address[IN]:寄存器地址
// 返    回：读出的值
unsigned char ReadRawRC(unsigned char Address)
{
    unsigned char ucAddr;
    unsigned char ucResult = 0;
    ucAddr = ((Address << 1) & 0x7E) | 0x80;
    HAL_Delay(1);
    RC522_ENABLE;
    // SPI_WriteNBytes(SPI1, &ucAddr, 1);  // 向总线写多个数据
    // SPI_ReadNBytes(SPI1, &ucResult, 1); // 向总线读多个数据
    HAL_SPI_Transmit(&hspi2, &ucAddr, 1, 0xff);
    HAL_SPI_Receive(&hspi2, &ucResult, 1, 0xff);
    RC522_DISABLE;
    return ucResult;
}
// 功    能：写RC632寄存器
// 参数说明：Address[IN]:寄存器地址
//           value[IN]:写入的值
void WriteRawRC(unsigned char Address, unsigned char value)
{
    unsigned char ucAddr;
    uint8_t write_buffer[2] = {0};
    ucAddr = ((Address << 1) & 0x7E);
    write_buffer[0] = ucAddr;
    write_buffer[1] = value;
    HAL_Delay(1);
    RC522_ENABLE;
    // SPI_WriteNBytes(SPI1, write_buffer, 2);
    HAL_SPI_Transmit(&hspi2, write_buffer, 2, 0xff);
    RC522_DISABLE;
}
// 功    能：置RC522寄存器位
// 参数说明：reg[IN]:寄存器地址
//           mask[IN]:置位值
void SetBitMask(unsigned char reg, unsigned char mask)
{
    char tmp = 0x0;
    tmp = ReadRawRC(reg);        // 读RC632寄存器
    WriteRawRC(reg, tmp | mask); // set bit mask
}
// 功    能：清RC522寄存器位
// 参数说明：reg[IN]:寄存器地址
//           mask[IN]:清位值
void ClearBitMask(unsigned char reg, unsigned char mask)
{
    char tmp = 0x0;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg, tmp & ~mask); // clear bit mask
}
// 功    能：通过RC522和ISO14443卡通讯
// 参数说明：Command[IN]:RC522命令字
//           pIn [IN]:通过RC522发送到卡片的数据
//           InLenByte[IN]:发送数据的字节长度
//           pOut [OUT]:接收到的卡片返回数据
//           *pOutLenBit[OUT]:返回数据的位长度
char PcdComMF522(unsigned char Command,
                 unsigned char *pInData,
                 unsigned char InLenByte,
                 unsigned char *pOutData,
                 unsigned int *pOutLenBit)
{
    char status = MI_ERR;
    unsigned char irqEn = 0x00;
    unsigned char waitFor = 0x00;
    unsigned char lastBits;
    unsigned char n;
    unsigned int i;
    switch (Command)
    {
    case PCD_AUTHENT:
        irqEn = 0x12;
        waitFor = 0x10;
        break;
    case PCD_TRANSCEIVE:
        irqEn = 0x77;
        waitFor = 0x30;
        break;
    default:
        break;
    }
    WriteRawRC(ComIEnReg, irqEn | 0x80);
    ClearBitMask(ComIrqReg, 0x80);
    WriteRawRC(CommandReg, PCD_IDLE);
    SetBitMask(FIFOLevelReg, 0x80);
    for (i = 0; i < InLenByte; i++)
    {
        WriteRawRC(FIFODataReg, pInData[i]);
    }
    WriteRawRC(CommandReg, Command);
    if (Command == PCD_TRANSCEIVE)
    {
        SetBitMask(BitFramingReg, 0x80);
    }
    i = 800;
    do
    {
        n = ReadRawRC(ComIrqReg);
        i--;
    } while ((i != 0) && !(n & 0x01) && !(n & waitFor));
    ClearBitMask(BitFramingReg, 0x80);
    if (i != 0)
    {
        if (!(ReadRawRC(ErrorReg) & 0x1B))
        {
            status = MI_OK;
            if (n & irqEn & 0x01)
            {
                status = MI_NOTAGERR;
            }
            if (Command == PCD_TRANSCEIVE)
            {
                n = ReadRawRC(FIFOLevelReg);
                lastBits = ReadRawRC(ControlReg) & 0x07;
                if (lastBits)
                {
                    *pOutLenBit = (n - 1) * 8 + lastBits;
                }
                else
                {
                    *pOutLenBit = n * 8;
                }
                if (n == 0)
                {
                    n = 1;
                }
                if (n > MAXRLEN)
                {
                    n = MAXRLEN;
                }
                for (i = 0; i < n; i++)
                {
                    pOutData[i] = ReadRawRC(FIFODataReg);
                }
            }
        }
        else
        {
            status = MI_ERR;
        }
    }
    SetBitMask(ControlReg, 0x80); // stop timer now
    WriteRawRC(CommandReg, PCD_IDLE);
    return status;
}
// 开启天线
// 每次启动或关闭天险发射之间应至少有1ms的间隔
void PcdAntennaOn(void)
{
    unsigned char i;
    i = ReadRawRC(TxControlReg);
    if (!(i & 0x03))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}
// 关闭天线
void PcdAntennaOff(void)
{
    ClearBitMask(TxControlReg, 0x03);
}

void RC522_Config(unsigned char Card_Type)
{
    ClearBitMask(Status2Reg, 0x08);
    WriteRawRC(ModeReg, 0x3D);
    WriteRawRC(RxSelReg, 0x86);
    WriteRawRC(RFCfgReg, 0x7F);
    WriteRawRC(TReloadRegL, 30);
    WriteRawRC(TReloadRegH, 0);
    WriteRawRC(TModeReg, 0x8D);
    WriteRawRC(TPrescalerReg, 0x3E);
    HAL_Delay(5);
    PcdAntennaOn();
}
