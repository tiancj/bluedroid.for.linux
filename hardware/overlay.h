/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_OVERLAY_INTERFACE_H
#define ANDROID_OVERLAY_INTERFACE_H

#include <cutils/native_handle.h>

#include <hardware/hardware.h>
#include <hardware/hwcomposer.h>
#include <stdint.h>
#include <sys/cdefs.h>
#include <sys/types.h>


__BEGIN_DECLS

/**
 * The id of this module
 */
 
#define OVERLAY_HARDWARE_MODULE_ID "overlay"
#define OVERLAY_HARDWARE   "overlay"
/*****************************************************************************/

/* possible overlay formats */
enum {
    OVERLAY_FORMAT_RGBA_8888    = HAL_PIXEL_FORMAT_RGBA_8888,
    OVERLAY_FORMAT_RGB_565      = HAL_PIXEL_FORMAT_RGB_565,
    OVERLAY_FORMAT_BGRA_8888    = HAL_PIXEL_FORMAT_BGRA_8888,
    OVERLAY_FORMAT_YUV_420 		  = HAL_PIXEL_FORMAT_YV12,
    OVERLAY_FORMAT_YUV_420_SP 	= HAL_PIXEL_FORMAT_YCrCb_420_SP,
    OVERLAY_FORMAT_CbYCrY_422_I = HAL_PIXEL_FORMAT_YCbCr_422_I,
    OVERLAY_FORMAT_DEFAULT      = 99    // The actual color format is determined
                                        // by the overlay
};

/* values for copybit_set_parameter(OVERLAY_TRANSFORM) */
enum {
    /* flip source image horizontally */
    OVERLAY_TRANSFORM_FLIP_H    = HAL_TRANSFORM_FLIP_H,
    /* flip source image vertically */
    OVERLAY_TRANSFORM_FLIP_V    = HAL_TRANSFORM_FLIP_V,
    /* rotate source image 90 degrees */
    OVERLAY_TRANSFORM_ROT_90    = HAL_TRANSFORM_ROT_90,
    /* rotate source image 180 degrees */
    OVERLAY_TRANSFORM_ROT_180   = HAL_TRANSFORM_ROT_180,
    /* rotate source image 270 degrees */
    OVERLAY_TRANSFORM_ROT_270   = HAL_TRANSFORM_ROT_270
};

/* names for setParameter() */
enum {
    /* rotation of the source image in degrees (0 to 359) */
    OVERLAY_ROTATION_DEG  = 1,
    /* enable or disable dithering */
    OVERLAY_DITHER        = 3,
    /* transformation applied (this is a superset of COPYBIT_ROTATION_DEG) */
    OVERLAY_TRANSFORM    = 4,
    
    OVERLAY_COLOR_KEY    = 5,
};

/* enable/disable value setParameter() */
enum {
    OVERLAY_DISABLE = 0,
    OVERLAY_ENABLE  = 1
};

/* names for get() */
enum {
    /* Maximum amount of minification supported by the hardware*/
    OVERLAY_MINIFICATION_LIMIT      = 1,
    /* Maximum amount of magnification supported by the hardware */
    OVERLAY_MAGNIFICATION_LIMIT     = 2,
    /* Number of fractional bits support by the overlay scaling engine */
    OVERLAY_SCALING_FRAC_BITS       = 3,
    /* Supported rotation step in degrees. */
    OVERLAY_ROTATION_STEP_DEG       = 4,
    /* horizontal alignment in pixels */
    OVERLAY_HORIZONTAL_ALIGNMENT    = 5,
    /* vertical alignment in pixels */
    OVERLAY_VERTICAL_ALIGNMENT      = 6,
    /* width alignment restrictions. negative number for max. power-of-two */
    OVERLAY_WIDTH_ALIGNMENT         = 7,
    /* height alignment restrictions. negative number for max. power-of-two */
    OVERLAY_HEIGHT_ALIGNMENT        = 8,
};
/*****************************************************************************/

/**
 * Every hardware module must have a data structure named HAL_MODULE_INFO_SYM
 * and the fields of this data structure must begin with hw_module_t
 * followed by module specific information.
 */
struct overlay_module_t {
    struct hw_module_t common;
};

typedef void * overlay_buffer_t;
/*****************************************************************************/
/**
 * Every device data structure must begin with hw_device_t
 * followed by module specific public methods and attributes.
 */
typedef struct overlay_device {
    struct hw_device_t common;
        
    int (*prepare)(struct overlay_device *dev,hwc_layer_t *layer);
    
    int (*set)(struct overlay_device *dev,hwc_layer_t *layer);
    
    int (*close)(struct overlay_device *dev);
    
} overlay_device_t;

struct overlay_context_t {		
    overlay_device_t device;
    
    /* our private state goes below here */
    
    /* control informations */
    int fd;            
    int mInit;            
    int isReady;
    int isFirst;
    
    /*out put window informations */
    uint32_t posX ;
		uint32_t posY ;
		uint32_t posW ;
		uint32_t posH ;
		uint32_t rotation;
				
		/*image informations */
		uint32_t imageW ;
		uint32_t imageH;
		uint32_t format;
		
		/*crop informations */
		uint32_t cropX;
		uint32_t cropY;
		uint32_t cropW;
		uint32_t cropH;
    

};

/** convenience API for opening and closing a device */
static inline int overlay_open(const struct hw_module_t* module,
        overlay_device_t** device) {
    return module->methods->open(module,
            OVERLAY_HARDWARE, (struct hw_device_t**)device);
}

static inline int overlay_close(overlay_device_t * device) {
    return device->common.close(&device->common);
}

__END_DECLS

#endif  // ANDROID_OVERLAY_INTERFACE_H
