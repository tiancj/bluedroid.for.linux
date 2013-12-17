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


#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "bt_mtk.h"


/**************************************************************************
 *                 G L O B A L   V A R I A B L E S                        *
***************************************************************************/

#ifndef MTK_COMBO_SUPPORT
#ifdef MTK_MT6622
static char BT_UPDATE_PATCH_FILE_NAME[64] = "/data/MTK_MT6622_E2_Patch.nb0";
static char BT_BUILT_IN_PATCH_FILE_NAME[64] = "/system/etc/firmware/MTK_MT6622_E2_Patch.nb0";
#endif
#endif

extern bt_vendor_callbacks_t *bt_vnd_cbacks;
extern sBTInitVar_t btinit[1];
extern sBTInitCB_t btinit_ctrl;

/**************************************************************************
 *                          F U N C T I O N S                             *
***************************************************************************/

extern void *GORM_FW_Init_Thread(void *ptr);

extern void *GORM_SCO_Init_Thread(void *ptr);


#ifndef MTK_COMBO_SUPPORT
static void BT_Load_Firmware_Patch(
    PBYTE*  ppbPatchExtBin,
    PDWORD  pPatchExtLen,
    PBYTE*  ppbPatchBin,
    PDWORD  pPatchLen
    )
{
    FILE* pPatchFile = NULL;
    
    LOG_DBG("BT load firmware patch\n");
    
    /* Use data directory first, for future update test convinience */
    pPatchFile = fopen(BT_UPDATE_PATCH_FILE_NAME, "rb");
    
    /* If there is no adhoc file, use built-in patch file under system etc firmware */
    if (pPatchFile == NULL){
        pPatchFile = fopen(BT_BUILT_IN_PATCH_FILE_NAME, "rb");
        if (pPatchFile == NULL) {
            LOG_ERR("Can't get valid patch file\n");
        }
        else {
            LOG_WAN("Open %s\n", BT_BUILT_IN_PATCH_FILE_NAME);
        }
    }
    else {
        LOG_WAN("Open %s\n", BT_UPDATE_PATCH_FILE_NAME);       
    }
    
    /* File exists */
    if (pPatchFile != NULL){
        if (fseek(pPatchFile, 0, SEEK_END) != 0){
            LOG_ERR("fseek patch file fails errno: %d\n", errno);
        }
        else{
            long lFileLen = 0;
            
            lFileLen = ftell(pPatchFile);
            if (lFileLen <= 0){
                LOG_ERR("Patch size error %d\n", (int)lFileLen);
            }
            else{
                LOG_DBG("Patch size %d\n", (int)lFileLen);
                /* Back to file beginning */
                rewind(pPatchFile);
                
                *ppbPatchBin = (unsigned char*)malloc(lFileLen);
                if (*ppbPatchBin == NULL){
                    LOG_ERR("Allocate patch memory fails\n");
                }
                else{
                    size_t szReadLen = 0;
                    szReadLen = fread(*ppbPatchBin, 1, lFileLen, pPatchFile);
                    
                    if(szReadLen != (size_t)lFileLen){
                        LOG_ERR("fread patch len error, file len: %d, read len: %d\n", (int)lFileLen, (int)szReadLen);
                        free(*ppbPatchBin);
                        *ppbPatchBin = NULL;
                        *pPatchLen = 0;
                    }
                    else{
                        *pPatchLen = szReadLen;
                    }
                }
            }      
        }
    }
    
    if(pPatchFile){
        fclose(pPatchFile);
        pPatchFile = NULL;
    }
    
    return;
}
#endif

BOOL BT_InitDevice(
    PBYTE   ucConfData,
    DWORD   dwBaud,
    DWORD   dwHostBaud,
    DWORD   dwFlowControl,
    SETUP_UART_PARAM  uart_setup_callback
    )
{
    
    LOG_DBG("BT_InitDevice\n");
    
    memset(btinit, 0, sizeof(sBTInitVar_t));
    
    // Copy configuration data
    memcpy(btinit->bt_conf.raw, ucConfData, sizeof(struct btradio_conf_data));
    // Save init variables, which are used on standalone chip case
    btinit->bt_baud = dwBaud;
    btinit->host_baud = dwHostBaud;
    btinit->flow_control = dwFlowControl;
    btinit->host_uart_cback = uart_setup_callback;
    
#ifndef MTK_COMBO_SUPPORT
    BT_Load_Firmware_Patch(
       NULL, 
       NULL, 
       &btinit->patch_data, 
       &btinit->patch_len);
    
    btinit->patch_offset = 0;
#endif

    if(pthread_create(&btinit_ctrl.worker_thread, NULL, \
                      GORM_FW_Init_Thread, (void*)btinit) != 0)
    {
        LOG_ERR("Create FW init thread fails\n");
        if (btinit->patch_data){
            free(btinit->patch_data);
            btinit->patch_data = NULL;
            btinit->patch_len = 0;
        }
        if (bt_vnd_cbacks){
            bt_vnd_cbacks->fwcfg_cb(BT_VND_OP_RESULT_FAIL);
        }
        return FALSE;
    }
    else{
        return TRUE;
    }
}

BOOL BT_InitSCO()
{
    LOG_DBG("BT_InitSCO\n");
    
    if(pthread_create(&btinit_ctrl.worker_thread, NULL, \
                      GORM_SCO_Init_Thread, (void*)btinit) != 0)
    {
        LOG_ERR("Create SCO init thread fails\n");
        return FALSE;
    }
    else{
        return TRUE;
    }
}