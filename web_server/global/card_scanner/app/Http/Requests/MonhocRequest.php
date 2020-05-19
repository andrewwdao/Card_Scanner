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
            'mamon'=>'required|unique:monhocs',
            'tenmon'=>'required',
            'sotiet'=>'required|numeric|min:30|max:75',
            'sotinchi'=>'required|numeric|min:2|max:4'
        ];
    }
    public function messages()
    {
        return [
        'mamon.required'=>"Mã môn trống!",
        'mamon.unique'=>"Mã môn bị trùng!",
        'tenmon.required'=>"Tên môn trống!",
        'sotiet.required'=>"Số tiết trống!",
        'sotiet.numeric'=>"Phải là kiểu số!",
        'sotiet.min'=>"Số tiết không nhỏ hơn 30!",
        'sotiet.max'=>"Số tiết không lớn hơn 75!",
        'sotinchi.required'=>"Số tín chỉ trống!",
        'sotinchi.numeric'=>"Phải là kiểu số!",
        'sotinchi.min'=>"Số tín chỉ không nhỏ hơn 2!",
        'sotinchi.max'=>"Số tín chỉ khong lớn hơn 4!",
        ];
    }
}
