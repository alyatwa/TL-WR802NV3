/*
 * Copyright (c) 2008, Atheros Communications Inc.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef _ATHR_7240_H
#define _ATHR_7240_H

/*
 * Config/Mac Register definitions
 */
#define ATHR_GMAC_CFG1                 0x00
#define ATHR_GMAC_CFG2                 0x04
#define ATHR_GMAC_IFCTL                0x38

/*
 * fifo control registers
 */
#define ATHR_GMAC_FIFO_CFG_0           0x48
#define ATHR_GMAC_FIFO_CFG_1           0x4c
#define ATHR_GMAC_FIFO_CFG_2           0x50
#define ATHR_GMAC_FIFO_CFG_3           0x54
#define ATHR_GMAC_FIFO_CFG_4           0x58

#define ATHR_GMAC_FIFO_CFG_5           0x5c
#define ATHR_GMAC_BYTE_PER_CLK_EN          (1 << 19)

#define ATHR_GMAC_FIFO_RAM_0           0x60
#define ATHR_GMAC_FIFO_RAM_1           0x64
#define ATHR_GMAC_FIFO_RAM_2           0x68
#define ATHR_GMAC_FIFO_RAM_3           0x6c
#define ATHR_GMAC_FIFO_RAM_4           0x70
#define ATHR_GMAC_FIFO_RAM_5           0x74
#define ATHR_GMAC_FIFO_RAM_6           0x78
#define ATHR_GMAC_FIFO_RAM_7           0x7c

/*
 * fields
 */
#define ATHR_GMAC_CFG1_SOFT_RST        (1 << 31)
#define ATHR_GMAC_CFG1_RX_RST          (1 << 19)
#define ATHR_GMAC_CFG1_TX_RST          (1 << 18)
#define ATHR_GMAC_CFG1_LOOPBACK        (1 << 8)
#define ATHR_GMAC_CFG1_RX_EN           (1 << 2)
#define ATHR_GMAC_CFG1_TX_EN           (1 << 0)
#define ATHR_GMAC_CFG1_RX_FCTL         (1 << 5)
#define ATHR_GMAC_CFG1_TX_FCTL         (1 << 4)


#define ATHR_GMAC_CFG2_FDX             (1 << 0)
#define ATHR_GMAC_CFG2_CRC_EN          (1 << 1)
#define ATHR_GMAC_CFG2_PAD_CRC_EN      (1 << 2)
#define ATHR_GMAC_CFG2_LEN_CHECK       (1 << 4)
#define ATHR_GMAC_CFG2_HUGE_FRAME_EN   (1 << 5)
#define ATHR_GMAC_CFG2_IF_1000         (1 << 9)
#define ATHR_GMAC_CFG2_IF_10_100       (1 << 8)

#define ATHR_GMAC_IFCTL_SPEED          (1 << 16)

/*
 * DMA (tx/rx) register defines
 */
#define ATHR_GMAC_DMA_TX_CTRL               0x180
#define ATHR_GMAC_DMA_TX_DESC               0x184
#define ATHR_GMAC_DMA_TX_STATUS             0x188
#define ATHR_GMAC_DMA_RX_CTRL               0x18c
#define ATHR_GMAC_DMA_RX_DESC               0x190
#define ATHR_GMAC_DMA_RX_STATUS             0x194
#define ATHR_GMAC_DMA_INTR_MASK             0x198
#define ATHR_GMAC_DMA_INTR                  0x19c
#define ATHR_GMAC_DMA_RXFSM		    0x1b0
#define ATHR_GMAC_DMA_TXFSM		    0x1b4
#define ATHR_GMAC_DMA_XFIFO_DEPTH	    0x1a8

/*
 * DMA status mask.
 */

#define ATHR_GMAC_DMA_DMA_STATE 	    0x3
#define ATHR_GMAC_DMA_AHB_STATE 	    0x7

/*
 * QOS register Defines 
 */

#define ATHR_GMAC_DMA_TX_CTRL_Q0            0x180
#define ATHR_GMAC_DMA_TX_CTRL_Q1            0x1C0
#define ATHR_GMAC_DMA_TX_CTRL_Q2            0x1C8
#define ATHR_GMAC_DMA_TX_CTRL_Q3            0x1D0

#define ATHR_GMAC_DMA_TX_DESC_Q0            0x184
#define ATHR_GMAC_DMA_TX_DESC_Q1            0x1C4
#define ATHR_GMAC_DMA_TX_DESC_Q2            0x1CC
#define ATHR_GMAC_DMA_TX_DESC_Q3            0x1D4

#define ATHR_GMAC_DMA_TX_ARB_CFG            0x1D8
#define ATHR_GMAC_TX_QOS_MODE_FIXED         0x0
#define ATHR_GMAC_TX_QOS_MODE_WEIGHTED      0x1
#define ATHR_GMAC_TX_QOS_WGT_0(x)	    ((x & 0x3F) << 8)
#define ATHR_GMAC_TX_QOS_WGT_1(x)	    ((x & 0x3F) << 14)
#define ATHR_GMAC_TX_QOS_WGT_2(x)	    ((x & 0x3F) << 20)
#define ATHR_GMAC_TX_QOS_WGT_3(x)	    ((x & 0x3F) << 26)

/*
 * tx/rx ctrl and status bits
 */
#define ATHR_GMAC_TXE                       (1 << 0)
#define ATHR_GMAC_TX_STATUS_PKTCNT_SHIFT    16
#define ATHR_GMAC_TX_STATUS_PKT_SENT        0x1
#define ATHR_GMAC_TX_STATUS_URN             0x2
#define ATHR_GMAC_TX_STATUS_BUS_ERROR       0x8

#define ATHR_GMAC_RXE                       (1 << 0)

#define ATHR_GMAC_RX_STATUS_PKTCNT_MASK     0xff0000
#define ATHR_GMAC_RX_STATUS_PKT_RCVD        (1 << 0)
#define ATHR_GMAC_RX_STATUS_OVF             (1 << 2)
#define ATHR_GMAC_RX_STATUS_BUS_ERROR       (1 << 3)

/*
 * Int and int mask
 */
#define ATHR_GMAC_INTR_TX                    (1 << 0)
#define ATHR_GMAC_INTR_TX_URN                (1 << 1)
#define ATHR_GMAC_INTR_TX_BUS_ERROR          (1 << 3)
#define ATHR_GMAC_INTR_RX                    (1 << 4)
#define ATHR_GMAC_INTR_RX_OVF                (1 << 6)
#define ATHR_GMAC_INTR_RX_BUS_ERROR          (1 << 7)

/*
 * MII registers
 */
#define ATHR_GMAC_MII_MGMT_CFG           0x20
#define ATHR_GMAC_MGMT_CFG_CLK_DIV_20        0x06
#define ATHR_GMAC_MII_MGMT_CMD               0x24
#define ATHR_GMAC_MGMT_CMD_READ              0x1
#define ATHR_GMAC_MII_MGMT_ADDRESS           0x28
#define ATHR_GMAC_ADDR_SHIFT                 8
#define ATHR_GMAC_MII_MGMT_CTRL              0x2c
#define ATHR_GMAC_MII_MGMT_STATUS            0x30
#define ATHR_GMAC_MII_MGMT_IND               0x34
#define ATHR_GMAC_MGMT_IND_BUSY              (1 << 0)
#define ATHR_GMAC_MGMT_IND_INVALID           (1 << 2)
#define ATHR_GMAC_GE_MAC_ADDR1               0x40
#define ATHR_GMAC_GE_MAC_ADDR2               0x44
#define ATHR_GMAC_MII0_CONTROL               0x18070000

/*
 * MIB Registers
 */
#define ATHR_GMAC_RX_PKT_CNTR		     0xa0
#define ATHR_GMAC_TX_PKT_CNTR		     0xe4
#define ATHR_GMAC_RX_BYTES_CNTR		     0x9c
#define ATHR_GMAC_TX_BYTES_CNTR		     0xe0
#define ATHR_GMAC_RX_LEN_ERR_CNTR  	     0xc0
#define ATHR_GMAC_RX_OVL_ERR_CNTR            0xd0
#define ATHR_GMAC_RX_CRC_ERR_CNTR	     0xa4
#define ATHR_GMAC_RX_FRM_ERR_CNTR	     0xbc
#define ATHR_GMAC_RX_CODE_ERR_CNTR	     0xc4
#define ATHR_GMAC_RX_CRS_ERR_CNTR	     0xc8
#define ATHR_GMAC_RX_DROP_CNTR		     0xdc
#define ATHR_GMAC_TX_DROP_CNTR		     0x114
#define ATHR_GMAC_RX_MULT_CNTR		     0xa8
#define ATHR_GMAC_TX_MULT_CNTR		     0xe8
#define ATHR_GMAC_TOTAL_COL_CNTR             0x10c
#define ATHR_GMAC_TX_CRC_ERR_CNTR	     0x11c

/*
 * Ethernet config registers 
 */
#define ATHR_GMAC_ETH_CFG                    0x18070000
#define ATHR_GMAC_ETH_CFG_RGMII_GE0          (1<<0)
#define ATHR_GMAC_ETH_CFG_MII_GE0            (1<<1)
#define ATHR_GMAC_ETH_CFG_GMII_GE0           (1<<2)
#define ATHR_GMAC_ETH_CFG_MII_GE0_MASTER     (1<<3)
#define ATHR_GMAC_ETH_CFG_MII_GE0_SLAVE      (1<<4)
#define ATHR_GMAC_ETH_CFG_GE0_ERR_EN         (1<<5)
#define ATHR_GMAC_ETH_CFG_SW_ONLY_MODE       (1<<6)
#define ATHR_GMAC_ETH_CFG_SW_PHY_SWAP        (1<<7)
#define ATHR_GMAC_ETH_CFG_SW_PHY_ADDR_SWAP   (1<<8)

#endif
