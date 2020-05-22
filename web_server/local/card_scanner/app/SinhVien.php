<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class SinhVien extends Model
{

    protected $table = 'sinhvien';
    protected $fillable=['mssv','ho','ten','gioi_tinh', 'id_mon'];
    public $timestamps=false;
    // public function lop()
    // {
    //     return $this->belongsTo('App\Lop');
    // }


}
