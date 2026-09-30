/*
 * Copyright (c) 2017 Guangdong OPPO Mobile Communication(shenzhen)
 * Corp.,Ltd. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials provided
 *       with the distribution.
 *     * Neither the name of The Linux Foundation nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once

#ifndef __VIDEO_LTM_H__
#define __VIDEO_LTM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>

#define STATS_HIST    0

#ifndef MAX_PLANE_NUM
#define MAX_PLANE_NUM 4
#endif

#ifndef __ErrorType__DEF__
#define __ErrorType__DEF__
    //General error codes for LTM API
    typedef enum _ErrorType {
        SUCCESS = 0,        /**< Operation success*/
        ERR_NULL_PTR,       /**< Input ptr is null.*/
        ERR_INVALID_FMT,    /**< Input format is invalid.*/
        ERROR               /**< Operation with error*/
    } ErrorType;

#endif

#ifndef __Datatype__DEF__
#define __Datatype__DEF__
    /**
    * General data types for LTM API. Note that
    * - YUV_P010_BIGEND,
    * - UBWC_TP10
    * are suppported by LTM Algorithms.
    */
    typedef enum _Datatype {
        UNKNOWN_IMAGE_DATATYPE = 0,

        // YUV
        YUV_420P_8BIT,              /**< YUV 420P (planar format Y....U..V.. */
        YUV_NV21_8BIT,              /**< YUV NV21 */
        YUV_NV12_8BIT,              /**< YUV NV12 */

        YUV_P010_LITTLEEND,         /**< Little end yuv p010 */
        YUV_420_10BIT_LITTLEEND,    /**< Little end YUV420 10-bit yuv (planar format Y....U..V.. */
        YUV_NV21_10BIT_LITTLEEND,   /**< Little end 10-bit YUV NV21 */
        YUV_NV12_10BIT_LITTLEEND,   /**< Little end 10-bit YUV NV12 */

        YUV_P010_BIGEND,            /**< Big end yuv p010 */
        YUV_420_10BIT_BIGEND,       /**< Big end YUV420 10-bit yuv (planar format Y....U..V.. */
        YUV_NV21_10BIT_BIGEND,      /**< Big end 10-bit YUV NV21 */
        YUV_NV12_10BIT_BIGEND,      /**< Big end YUV NV12 */

        // Qcom Exten
        UBWC_TP10,                  /**< Qcom UBWC_TP10 */
        UBWC_NV12,                  /**< Qcom UBWC_NV12 */
        YUV_PD10,                   /**< Qcom PD10 */

        // RGB
        RGBFFF,                     /**< 16*3-bit RGB */
        RGBAAA,                     /**< 10*3-bit RGB */
        RGB565,                     /**< RGB565 */
        RGB888,                     /**< 24-bit RGB */
        RGBA8888,                   /**< 32-bit RGB+A*/

        // Luma
        LUMA_10BIT,                 /**< 10-bit Luma*/
        LUMA_8BIT,                  /**< 8-bit Luma*/

    } Datatype;

#endif //__Datatype__DEF__

#ifndef __CAMERA_TYPE__DEF__
#define __CAMERA_TYPE__DEF__
    /**
    * General Camera type for LTM API.
    */

    typedef enum _CAMERA_TYPE
    {
        MAIN_CAMERA     = 0,
        FRONT_CAMERA    = 1,
        WIDE_CAMERA     = 2,
        TELE_CAMERA     = 3,
        ULTRA_TELE_CAMERA = 4
    } CAMERA_TYPE;

#endif //__CAMERA_TYPE__DEF__

#ifndef __IMAGE_TYPE__DEF__
#define __IMAGE_TYPE__DEF__

    /**
    * Structure for general multi-plane image to be used
    * for many algorithms
    */

    typedef struct IMAGE
    {
        Datatype type;
        int planeNum;
        int width;
        int height;
        int bitDepth;
        int stride[MAX_PLANE_NUM];
        int scanline[MAX_PLANE_NUM];
        unsigned char *imagePlane[MAX_PLANE_NUM];
        int share_fd[MAX_PLANE_NUM] = {-1};
    }IMAGE;

#endif //__IMAGE_TYPE__DEF__


#ifndef __ConfigPara__DEF__
#define __ConfigPara__DEF__

    /**
    * Structure for project info
    */

    typedef struct _ConfigPara
    {
        int logLevel;
        CAMERA_TYPE cameraType;
        int projectVersion;
        int ltmEnable = 0;

    } ConfigPara;

#endif //__ConfigPara__DEF__

#ifndef __AecInfo__DEF__
#define __AecInfo__DEF__

    /**
    * Structure for general Aec Infomation.
    */

    typedef struct
    {
        int    left;      ///< X coordinate of the rectangle.
        int    top;       ///< Y coordinate of the rectangle.
        int    width;     ///< Width of the rectangle.
        int    height;    ///< Height of the rectangle.
    } FaceRectInfo;

    typedef struct _AecInfo
    {
        float luxIndex;
        float isoValue;
        float drcGain;
        float darkBoostGain;
        float aecSettled;
        float shortExpTime;
        float longExpTime;
        float shortGain;
        float longGain;
        float aecSensitivity;
        float CCT;
        int faceNum;
        FaceRectInfo faceRect;
    }  AecInfo;

    typedef struct __SyncInfo
    {
        int frameNum;
        int isDolby;
        int isMovie;
        int isViull;
        int isasdUiValue;
        int fps; // 30/60
        int videoResolution; // 4K / 2K
        int isDehazing;
        int isRecording;
        float GyroInfo[64];
        int   cameraID;
        float ipeGammaPower;
        uint32_t* ifeGammaTab;
    } SyncInfo;

#endif // __AecInfo__DEF__

#ifndef __TMCImageList_DEF__
#define __TMCImageList_DEF__

     /**
    * Structure for all I/O Image Ptr.
    */

   typedef struct __ImageList
   {
        IMAGE* pInput2K     = nullptr;
        IMAGE* pInput4K     = nullptr;
        IMAGE* pInput2KDS4  = nullptr;
        IMAGE* pInput4KDS4  = nullptr;
        IMAGE* pInput2KDS16 = nullptr;
        IMAGE* pInput4KDS16 = nullptr;

        IMAGE* pOutput2K        = nullptr;
        IMAGE* pOutput4K        = nullptr;
        IMAGE* pOutput2KDS4     = nullptr;
        IMAGE* pOutput4KDS4     = nullptr;
        IMAGE* pOutput2KDS16    = nullptr;
        IMAGE* pOutput4KDS16    = nullptr;
   } ImageList;

#endif // __TMCImageList_DEF__

#ifndef __LTMPars_DEF__
#define __LTMPars_DEF__

    /**
    * LTM Pars
    */

   typedef struct __LTMPars
   {
        float ltm_scale[65] = { 0 };
        int mask_rect_curve[65] = { 0 };
        float lce_scale_pos[17] = { 0 };
        float lce_scale_neg[17] = { 0 };
        float ltm_strength;
        float dark_boost;
        float bright_suppress;
        float lce_strength;
        float blend_weight[12] = { 0 };
        float face_ltm;
        float face_lce;
        int ltm_enable = 1;
   } LTMPars;
#endif // __LTMPars_DEF__

#ifndef __TDLPars_DEF__
#define __TDLPars_DEF__
    typedef struct __TDLPars
    {
        float lut_1d_h[25] = { 0 };
        float lut_2d_h[384] = { 0 };
        float lut_2d_s[384] = { 0 };
        float l_boundary_start_a = 0;
        float l_boundary_start_b = 0.69;
        float l_boundary_end_a = 0.99;
        float l_boundary_end_b = 1;
        float l_boundary_x2 = 0.6;
        float l_boundary_y2 = 0;
        float l_boundary_x5 = 0.7;
        float l_boundary_y5 = 1;
        float y_blend_factor_integer = 1.0;
        int tdl_enable = 1;
        int tdl_video_enable;
   } TDLPars;
#endif // __TDLPars_DEF__

#ifndef __GammaPars_DEF__
#define __GammaPars_DEF__
    typedef struct __GammaPars
    {
        float pGammaRWeight[257] = { 0 };
        float pGammaGWeight[257] = { 0 };
        float pGammaBWeight[257] = { 0 };
        float IpeGammaPower;
        uint32_t pIFEGamma[257] = { 0 };
        int gamma_enable = 1;
        int gamma_video_enable;
    } GammaPars;

#endif // __GammaPars_DEF__

#ifndef __GTMPars_DEF__
#define __GTMPars_DEF__
    typedef struct __GTMPars
    {
        float pGTMTable[257] = { 0 };
        int gtm_enable = 1;
    } GTMPars;

#endif // __GTMPars_DEF__

#ifndef __PostNodePars_DEF__
#define __PostNodePars_DEF__
    typedef struct __PostNodePars
    {
        float* genHistLUT;
        int dehaze_flag;
        float mlft_strength;
        float skin_protect_str;
    } PostNodePars;

#endif // __PostNodePars_DEF__

class VideoMLFTAlgo
{

private:
    static PostNodePars m_post_pars;
    static PostNodePars* m_post_pars_arr;
    static uint32_t m_frameId;

public:
    VideoMLFTAlgo() {}
    virtual ~VideoMLFTAlgo() {}


    /**
    * @brief Init Source
    * @return Error code indicating if execution was succeed or failed.
    **/
    void* Video_Ltm_Initial(ConfigPara* pConfig, SyncInfo *pSyncInfo);

    ErrorType Video_Ltm_Process_mid(void *pHandle, ImageList imageList, AecInfo *pAecInfo, SyncInfo *pSyncInfo, GammaPars *pGammaWeight, LTMPars *pLTMPars, TDLPars *pTDLPars, GTMPars *pGTMPars);

    ErrorType Video_Ltm_Process_post(void *pHandle, ImageList imageList, AecInfo *pAecInfo, SyncInfo *pSyncInfo, GammaPars *pGammaWeight, LTMPars *pLTMPars, TDLPars *pTDLPars, GTMPars *pGTMPars);

    /**
    * @brief Uninit Source
    * @return Error code indicating if execution was succeed (SUCCESS) or failed (ERROR)
    **/
    ErrorType Video_Ltm_Release(void* pHandle);

    /**
    * Get ltm library string.
    * @return string
    **/
    const char* Video_Ltm_Getversion(void);

    /**
    * @brief Check if given type (format) is supported
    * @param type check this type
    * @return Error code indicating if support (SUCCESS) unsupport (ERR_INVALID_FMT)
    */
    ErrorType Video_Ltm_IsSupportedFormat(Datatype type);
};

#ifdef __cplusplus
}
#endif

#endif //__VIDEO_LTM_H__