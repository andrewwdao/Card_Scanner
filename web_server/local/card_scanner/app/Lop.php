<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Lop extends Model
{
    //
    protected $table = 'lops';
    protected $fillable=['id','malop','tenlop'];
    public $timestamps=false;
    // public function lop()
    // {
    // 	return $this->hasMany('App\SinhVien');
    // }
}
