<?php

namespace App\Http\Requests;

use Illuminate\Foundation\Http\FormRequest;

class MonhocRequest extends FormRequest
{
    /**
     * Determine if the user is authorized to make this request.
     *
     * @return bool
     */
    public function authorize()
    {
        return true;
    }

    /**
     * Get the validation rules that apply to the request.
     *
     * @return array
     */
    public function rules()
    {
        return [
            //
            'ma_mon'=>'required',
            'ten_mon'=>'required',
            // 'so_tiet'=>'required|numeric|min:30|max:75',
            // 'so_tin_chi'=>'required|numeric|min:2|max:4',
            'hoc_ky' => 'numeric|min:1|max:3',
            'so_buoi'=>'required|numeric',
            'buoi' => 'required'
        ];
    }
    public function messages()
    {
        return [
        'ma_mon.required'=>"Mã môn trống!",
        'ma_mon.unique'=>"Mã môn bị trùng!",
        'ten_mon.required'=>"Tên môn trống!",
        // 'so_tiet.required'=>"Số tiết trống!",
        // 'so_tiet.numeric'=>"Phải là kiểu số!",
        // 'so_tiet.min'=>"Số tiết không nhỏ hơn 30!",
        // 'so_tiet.max'=>"Số tiết không lớn hơn 75!",
        // 'so_tin_chi.required'=>"Số tín chỉ trống!",
        // 'so_tin_chi.numeric'=>"Phải là kiểu số!",
        // 'so_tin_chi.min'=>"Số tín chỉ không nhỏ hơn 2!",
        // 'so_tin_chi.max'=>"Số tín chỉ khong lớn hơn 4!",
        'buoi.required'=>"Buổi học không được trống",
        'so_buoi.required'=>"Số buổi không được trống",
        'so_buoi.numeric' => 'Số buổi phải là số',
        'hoc_ky.numeric'=>"Học kỳ phải là 1, 2 hoặc 3",
        'hoc_ky.min'=>"Học kỳ phải là 1, 2 hoặc 3",
        'hoc_ky.max'=>"Học kỳ phải là 1, 2 hoặc 3",
        // 'nam_hoc.numeric'=>"Năm học phải lớn hơn 2000",
        // 'nam_hoc.min'=>"Năm học phải lớn hơn 2020",
        ];
    }
}
