/*
 * Copyright (C) 2016, Device++. All rights reserved.
 * Copyright (C) 2016, Vankia Inc. All rights reserved.
 *
 * Created at 2016-09-21, Huang Rui <vowstar@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY DEVICE++. OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
 * POSSIBILITY OF SUCH DAMAGE. 
 */

#ifndef __WIFI_UTILS_H__
#define __WIFI_UTILS_H__

#ifdef __cplusplus
extern "C" {
#endif

void wifi_connect(void);
void wifi_setup_ap(void);
void wifi_setup_sta(void);
uint8_t wifi_station_get_connect_status(void);
void wifi_subsystem_init(void);

#ifdef __cplusplus
}
#endif

#endif /*  __WIFI_UTILS_H__ */