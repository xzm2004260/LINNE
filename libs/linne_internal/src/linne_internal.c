#include "linne_internal.h"

/* 配列の要素数を取得 */
#define LINNE_NUM_ARRAY_ELEMENTS(array) ((sizeof(array)) / (sizeof(array[0])))
/* プリセットの要素定義 */
#define LINNE_DEFINE_PARAMETER_PRESET(array) \
    {\
        LINNE_NUM_ARRAY_ELEMENTS(array),\
        array\
    }

static const uint32_t num_params_preset1[] = {  8,  8,  8 };
static const uint32_t num_params_preset2[] = { 16, 16, 16 };
static const uint32_t num_params_preset3[] = { 32, 32, 32 };

/* パラメータプリセット配列 */
const struct LINNEParameterPreset g_linne_parameter_preset[LINNE_NUM_PARAMETER_PRESETS] = {
    LINNE_DEFINE_PARAMETER_PRESET(num_params_preset1),
    LINNE_DEFINE_PARAMETER_PRESET(num_params_preset2),
    LINNE_DEFINE_PARAMETER_PRESET(num_params_preset3),
};