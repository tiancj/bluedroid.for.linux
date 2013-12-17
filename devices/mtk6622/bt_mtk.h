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

#ifndef _BT_MTK_H
#define _BT_MTK_H

#include <pthread.h>
#include "bt_hci_bdroid.h"
#include "bt_vendor_lib.h"
#include "custom/CFG_BT_File.h"
#include "os_dep.h"


#define CUSTOM_BT_CFG_FILE          "/data/BT.cfg"
#define INTERNAL_BT_CFG_FILE        "/data/bluetooth/BT.cfg"


#define HCI_CMD_MAX_SIZE        251


/**********  Structures & Definitions  ************/

typedef enum {
	CMD_SUCCESS,
	CMD_FAIL,
	CMD_PENDING,
} HciCmdStatus_t;

typedef BOOL (*tHciCmdFunc) (HC_BT_HDR *);
typedef struct {
	tHciCmdFunc command_func;
} sHciScriptElement_t;

typedef union {
	struct btradio_conf_data fields;
	unsigned char raw[sizeof(struct btradio_conf_data)];
} BTConfData_t;


typedef int (*SETUP_UART_PARAM)(int iBaudrate, int iFlowControl);


typedef struct {
	BTConfData_t bt_conf;
	DWORD  bt_baud;
	DWORD  host_baud;
	DWORD  flow_control;
	SETUP_UART_PARAM host_uart_cback;
	PUCHAR patch_ext_data;
	DWORD  patch_ext_len;
	DWORD  patch_ext_offset;
	PUCHAR patch_data;
	DWORD  patch_len;
	DWORD  patch_offset;
	sHciScriptElement_t* cur_script;
} sBTInitVar_t;

/* thread control block for Controller initialize */
typedef struct {
	pthread_t worker_thread;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} sBTInitCB_t;


/*****************    APIs    ******************/
void set_callbacks(const bt_vendor_callbacks_t* p_cb);
void clean_callbacks();
int set_bluetooth_power(int on);
int init_uart();
void close_uart();
int mtk_fw_cfg();
int mtk_sco_cfg();

#endif
