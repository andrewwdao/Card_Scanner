<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class monhoc extends Model
{
    //
    protected $table = 'monhoc';
    protected $fillable=['ma_mon','ten_mon', 'hoc_ky', 'nam_hoc', 'so_tin_chi','so_tiet'];
	public $timestamps=false;
}
