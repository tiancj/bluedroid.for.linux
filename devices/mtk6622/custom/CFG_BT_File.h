/* Copyright Statement:
 *
 * This software/firmware and related documentation ("MediaTek Software") are
 * protected under relevant copyright laws. The information contained herein is
 * confidential and proprietary to MediaTek Inc. and/or its licensors. Without
 * the prior written permission of MediaTek inc. and/or its licensors, any
 * reproduction, modification, use or disclosure of MediaTek Software, and
 * information contained herein, in whole or in part, shall be strictly
 * prohibited.
 * 
 * MediaTek Inc. (C) 2010. All rights reserved.
 * 
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE")
 * RECEIVED FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO RECEIVER
 * ON AN "AS-IS" BASIS ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR
 * NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY WHATSOEVER WITH
 * RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 * INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND RECEIVER AGREES
 * TO LOOK ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO.
 * RECEIVER EXPRESSLY ACKNOWLEDGES THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO
 * OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES CONTAINED IN MEDIATEK
 * SOFTWARE. MEDIATEK SHALL ALSO NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE
 * RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S
 * ENTIRE AND CUMULATIVE LIABILITY WITH RESPECT TO THE MEDIATEK SOFTWARE
 * RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION, TO REVISE OR REPLACE THE
 * MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE
 * CHARGE PAID BY RECEIVER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 * The following software/firmware and/or related documentation ("MediaTek
 * Software") have been modified by MediaTek Inc. All revisions are subject to
 * any receiver's applicable license agreements with MediaTek Inc.
 */


#ifndef _CFG_BT_FILE_H
#define _CFG_BT_FILE_H


#ifdef MTK_COMBO_SUPPORT
///////////// Combo Chip MT6620, MT6628
struct btradio_conf_data
{
    unsigned char addr[6];            // BT address
    unsigned char voice[2];           // Voice setting for SCO connection
    unsigned char codec[4];           // PCM codec setting
    unsigned char radio[6];           // RF configuration
    unsigned char sleep[7];           // Sleep mode configuration
    unsigned char feature[2];         // Other feature setting
    unsigned char tx_pwr_offset[3];   // TX power channel offset compensation (MT6620)
};

static struct btradio_conf_data sDefaultCfg =
{
#if defined(MTK_MT6620)
    {0x00, 0x00, 0x46, 0x66, 0x20, 0x01},
#else
    {0x00, 0x00, 0x46, 0x66, 0x28, 0x01},
#endif
    {0x60, 0x00},
    {0x23, 0x10, 0x00, 0x00},
#if defined(MTK_MT6620)
    {0x06, 0x80, 0x00, 0x06, 0x03, 0x06},
#else
    {0x07, 0x80, 0x00, 0x06, 0x05, 0x07},
#endif
    {0x03, 0x40, 0x1F, 0x40, 0x1F, 0x00, 0x04},
    {0x80, 0x00},
    {0xFF, 0xFF, 0xFF}
};
#else
///////////// Standalone Chip MT6622, MT6626
struct btradio_conf_data
{
    unsigned char addr[6];            // BT address
    unsigned char capId[1];           // Calibration setting
    unsigned char link_key_type[1];   // Link key type
    unsigned char unit_key[16];       // Default unit key
    unsigned char encryption[3];      // Encryption setting
    unsigned char pin_code_type[1];   // Pin code type used for pairing
    unsigned char voice[2];           // Voice setting for SCO connection
    unsigned char codec[4];           // PCM codec setting
    unsigned char radio[6];           // RF configuration
    unsigned char sleep[7];           // Sleep mode configuration
    unsigned char feature[2];         // Other feature setting
    unsigned char ECLK_SEL[1];        // Select external clock (MT6626)
};

static struct btradio_conf_data sDefaultCfg =
{
#if defined(MTK_MT6622)
    {0x00, 0x00, 0x46, 0x66, 0x22, 0x01},
#else
    {0x00, 0x00, 0x46, 0x66, 0x26, 0x01},
#endif
    {0x40},
    {0x01},
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
    {0x00, 0x02, 0x10},
    {0x00},
    {0x60, 0x00},
    {0x23, 0x00, 0x00, 0x00},
    {0x07, 0x80, 0x00, 0x06, 0x03, 0x07},
    {0x00, 0x40, 0x1F, 0x00, 0x00, 0x00, 0x04},
    {0x80, 0x00},
    {0x00}
};
#endif
#endif