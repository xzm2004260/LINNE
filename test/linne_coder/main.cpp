#include <stdlib.h>
#include <string.h>

#include <gtest/gtest.h>

/* テスト対象のモジュール */
extern "C" {
#include "../../libs/linne_coder/src/linne_coder.c"
}

/* ハンドル作成破棄テスト */
TEST(LINNECoderTest, CreateDestroyHandleTest)
{
    /* ワークサイズ計算テスト */
    {
        int32_t work_size;

        /* 最低限構造体本体よりは大きいはず */
        work_size = LINNECoder_CalculateWorkSize();
        ASSERT_TRUE(work_size > sizeof(struct LINNECoder));
    }

    /* ワーク領域渡しによるハンドル作成（成功例） */
    {
        void *work;
        int32_t work_size;
        struct LINNECoder *coder;

        work_size = LINNECoder_CalculateWorkSize();
        work = malloc(work_size);

        coder = LINNECoder_Create(work, work_size);
        ASSERT_TRUE(coder != NULL);
        EXPECT_TRUE(coder->work == work);
        EXPECT_EQ(coder->alloced_by_own, 0);

        LINNECoder_Destroy(coder);
        free(work);
    }

    /* 自前確保によるハンドル作成（成功例） */
    {
        struct LINNECoder *coder;

        coder = LINNECoder_Create(NULL, 0);
        ASSERT_TRUE(coder != NULL);
        EXPECT_TRUE(coder->work != NULL);
        EXPECT_EQ(coder->alloced_by_own, 1);

        LINNECoder_Destroy(coder);
    }

    /* ワーク領域渡しによるハンドル作成（失敗ケース） */
    {
        void *work;
        int32_t work_size;
        struct LINNECoder *coder;

        work_size = LINNECoder_CalculateWorkSize();
        work = malloc(work_size);

        /* 引数が不正 */
        coder = LINNECoder_Create(NULL, work_size);
        EXPECT_TRUE(coder == NULL);
        coder = LINNECoder_Create(work, 0);
        EXPECT_TRUE(coder == NULL);

        /* ワークサイズ不足 */
        coder = LINNECoder_Create(work, work_size - 1);
        EXPECT_TRUE(coder == NULL);
    }
}

/* 再帰的ライス符号テスト */
TEST(LINNECoderTest, RecursiveRiceTest)
{
    /* 簡単に出力テスト */
    {
        uint32_t code;
        uint8_t data[16];
        struct BitStream strm;
        RecursiveRiceParameter param_array[2] = {0, 0};

        /* 0を4回出力 */
        memset(data, 0, sizeof(data));
        LINNECODER_PARAMETER_SET(param_array, 0, 1);
        LINNECODER_PARAMETER_SET(param_array, 1, 1);
        BitWriter_Open(&strm, data, sizeof(data));
        LINNERecursiveRice_PutCode(&strm, param_array, 0);
        LINNERecursiveRice_PutCode(&strm, param_array, 0);
        LINNERecursiveRice_PutCode(&strm, param_array, 0);
        LINNERecursiveRice_PutCode(&strm, param_array, 0);
        BitStream_Close(&strm);

        /* 取得 */
        LINNECODER_PARAMETER_SET(param_array, 0, 1);
        LINNECODER_PARAMETER_SET(param_array, 1, 1);
        BitReader_Open(&strm, data, sizeof(data));
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(0, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(0, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(0, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(0, code);
        BitStream_Close(&strm);

        /* 1を4回出力 */
        memset(data, 0, sizeof(data));
        LINNECODER_PARAMETER_SET(param_array, 0, 1);
        LINNECODER_PARAMETER_SET(param_array, 1, 1);
        BitWriter_Open(&strm, data, sizeof(data));
        LINNERecursiveRice_PutCode(&strm, param_array, 1);
        LINNERecursiveRice_PutCode(&strm, param_array, 1);
        LINNERecursiveRice_PutCode(&strm, param_array, 1);
        LINNERecursiveRice_PutCode(&strm, param_array, 1);
        BitStream_Close(&strm);

        /* 取得 */
        LINNECODER_PARAMETER_SET(param_array, 0, 1);
        LINNECODER_PARAMETER_SET(param_array, 1, 1);
        BitReader_Open(&strm, data, sizeof(data));
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(1, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(1, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(1, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(1, code);
        BitStream_Close(&strm);


        /* パラメータを変えて0を4回出力 */
        memset(data, 0, sizeof(data));
        LINNECODER_PARAMETER_SET(param_array, 0, 2);
        LINNECODER_PARAMETER_SET(param_array, 1, 2);
        BitWriter_Open(&strm, data, sizeof(data));
        LINNERecursiveRice_PutCode(&strm, param_array, 0);
        LINNERecursiveRice_PutCode(&strm, param_array, 0);
        LINNERecursiveRice_PutCode(&strm, param_array, 0);
        LINNERecursiveRice_PutCode(&strm, param_array, 0);
        BitStream_Close(&strm);

        /* 取得 */
        LINNECODER_PARAMETER_SET(param_array, 0, 2);
        LINNECODER_PARAMETER_SET(param_array, 1, 2);
        BitReader_Open(&strm, data, sizeof(data));
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(0, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(0, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(0, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(0, code);
        BitStream_Close(&strm);

        /* パラメータを変えて3を4回出力 */
        memset(data, 0, sizeof(data));
        LINNECODER_PARAMETER_SET(param_array, 0, 2);
        LINNECODER_PARAMETER_SET(param_array, 1, 2);
        BitWriter_Open(&strm, data, sizeof(data));
        LINNERecursiveRice_PutCode(&strm, param_array, 3);
        LINNERecursiveRice_PutCode(&strm, param_array, 3);
        LINNERecursiveRice_PutCode(&strm, param_array, 3);
        LINNERecursiveRice_PutCode(&strm, param_array, 3);
        BitStream_Close(&strm);

        /* 取得 */
        LINNECODER_PARAMETER_SET(param_array, 0, 2);
        LINNECODER_PARAMETER_SET(param_array, 1, 2);
        BitReader_Open(&strm, data, sizeof(data));
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(3, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(3, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(3, code);
        code = LINNERecursiveRice_GetCode(&strm, param_array);
        EXPECT_EQ(3, code);
        BitStream_Close(&strm);
    }

    /* 長めの信号を出力してみる */
    {
#define TEST_OUTPUT_LENGTH (128)
        uint32_t i, code, is_ok;
        struct BitStream strm;
        RecursiveRiceParameter param_array[2] = {0, 0};
        uint32_t test_output_pattern[TEST_OUTPUT_LENGTH];
        uint8_t data[TEST_OUTPUT_LENGTH * 2];

        /* 出力の生成 */
        for (i = 0; i < TEST_OUTPUT_LENGTH; i++) {
            test_output_pattern[i] = i;
        }

        /* 出力 */
        LINNECODER_PARAMETER_SET(param_array, 0, 1);
        LINNECODER_PARAMETER_SET(param_array, 1, 1);
        BitWriter_Open(&strm, data, sizeof(data));
        for (i = 0; i < TEST_OUTPUT_LENGTH; i++) {
            LINNERecursiveRice_PutCode(&strm, param_array, test_output_pattern[i]);
        }
        BitStream_Close(&strm);

        /* 取得 */
        LINNECODER_PARAMETER_SET(param_array, 0, 1);
        LINNECODER_PARAMETER_SET(param_array, 1, 1);
        BitReader_Open(&strm, data, sizeof(data));
        is_ok = 1;
        for (i = 0; i < TEST_OUTPUT_LENGTH; i++) {
            code = LINNERecursiveRice_GetCode(&strm, param_array);
            if (code != test_output_pattern[i]) {
                printf("actual:%d != test:%d \n", code, test_output_pattern[i]);
                is_ok = 0;
                break;
            }
        }
        EXPECT_EQ(1, is_ok);
        BitStream_Close(&strm);
#undef TEST_OUTPUT_LENGTH
    }

    /* 長めの信号を出力してみる（乱数） */
    {
#define TEST_OUTPUT_LENGTH (128)
        uint32_t i, code, is_ok;
        struct BitStream strm;
        RecursiveRiceParameter param_array[2] = {0, 0};
        uint32_t test_output_pattern[TEST_OUTPUT_LENGTH];
        uint8_t data[TEST_OUTPUT_LENGTH * 2];

        /* 出力の生成 */
        srand(0);
        for (i = 0; i < TEST_OUTPUT_LENGTH; i++) {
            test_output_pattern[i] = rand() % 0xFF;
        }

        /* 出力 */
        LINNECODER_PARAMETER_SET(param_array, 0, 1);
        LINNECODER_PARAMETER_SET(param_array, 1, 1);
        BitWriter_Open(&strm, data, sizeof(data));
        for (i = 0; i < TEST_OUTPUT_LENGTH; i++) {
            LINNERecursiveRice_PutCode(&strm, param_array, test_output_pattern[i]);
        }
        BitStream_Close(&strm);

        /* 取得 */
        LINNECODER_PARAMETER_SET(param_array, 0, 1);
        LINNECODER_PARAMETER_SET(param_array, 1, 1);
        BitReader_Open(&strm, data, sizeof(data));
        is_ok = 1;
        for (i = 0; i < TEST_OUTPUT_LENGTH; i++) {
            code = LINNERecursiveRice_GetCode(&strm, param_array);
            if (code != test_output_pattern[i]) {
                printf("actual:%d != test:%d \n", code, test_output_pattern[i]);
                is_ok = 0;
                break;
            }
        }
        EXPECT_EQ(1, is_ok);
        BitStream_Close(&strm);
#undef TEST_OUTPUT_LENGTH
    }

    /* 実データを符号化してみる */
    {
        uint32_t i, encsize;
        struct stat fstat;
        const char test_infile_name[] = "PriChanIcon.png";
        uint8_t*    fileimg;
        uint8_t*    encimg;
        uint8_t*    decimg;
        FILE*       fp;
        struct BitStream strm;
        RecursiveRiceParameter param_array[2];

        /* 入力データ読み出し */
        stat(test_infile_name, &fstat);
        fileimg = (uint8_t *)malloc(fstat.st_size);
        encimg  = (uint8_t *)malloc(2 * fstat.st_size);  /* PNG画像のため増えることを想定 */
        decimg  = (uint8_t *)malloc(fstat.st_size);
        fp = fopen(test_infile_name, "rb");
        fread(fileimg, sizeof(uint8_t), fstat.st_size, fp);
        fclose(fp);

        /* 書き込み */
        BitWriter_Open(&strm, encimg, 2 * fstat.st_size);
        LINNECODER_PARAMETER_SET(param_array, 0, 1);
        LINNECODER_PARAMETER_SET(param_array, 1, 1);
        for (i = 0; i < fstat.st_size; i++) {
            LINNERecursiveRice_PutCode(&strm, param_array, fileimg[i]);
        }
        BitStream_Flush(&strm);
        BitStream_Tell(&strm, (int32_t *)&encsize);
        BitStream_Close(&strm);

        /* 読み込み */
        BitReader_Open(&strm, encimg, encsize);
        LINNECODER_PARAMETER_SET(param_array, 0, 1);
        LINNECODER_PARAMETER_SET(param_array, 1, 1);
        for (i = 0; i < fstat.st_size; i++) {
            decimg[i] = (uint8_t)LINNERecursiveRice_GetCode(&strm, param_array);
        }
        BitStream_Close(&strm);

        /* 一致確認 */
        EXPECT_EQ(0, memcmp(fileimg, decimg, sizeof(uint8_t) * fstat.st_size));

        free(decimg);
        free(fileimg);
    }

}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
