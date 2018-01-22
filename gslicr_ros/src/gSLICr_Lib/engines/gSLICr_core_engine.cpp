// Copyright 2014-2015 Isis Innovation Limited and the authors of gSLICr

#pragma once
#include <vector>

#include "gSLICr_core_engine.h"

using namespace gSLICr;
using namespace std;

gSLICr::engines::core_engine::core_engine(const objects::settings& in_settings)
{
	slic_seg_engine = new seg_engine_GPU(in_settings);
}

gSLICr::engines::core_engine::~core_engine()
{
		delete slic_seg_engine;
}

void gSLICr::engines::core_engine::Process_Frame(UChar4Image* in_img)
{
	slic_seg_engine->Perform_Segmentation(in_img);
}

const IntImage * gSLICr::engines::core_engine::Get_Seg_Res()
{
	return slic_seg_engine->Get_Seg_Mask();
}

void gSLICr::engines::core_engine::Draw_Segmentation_Result(UChar4Image* out_img)
{
	slic_seg_engine->Draw_Segmentation_Result(out_img);
}

void gSLICr::engines::core_engine::Write_Seg_Res_To_Array(vector<short unsigned int>& lable_array)
{
	const IntImage* idx_img = slic_seg_engine->Get_Seg_Mask();
	int width = idx_img->noDims.x;
	int height = idx_img->noDims.y;
	const int* data_ptr = idx_img->GetData(MEMORYDEVICE_CPU);
	for (int i = 0; i < height * width; ++i)
	{
		ushort lable = (ushort)data_ptr[i];
		lable_array[i]=lable;
		ushort lable_buffer = (lable << 8 | lable >> 8);
	}
}
