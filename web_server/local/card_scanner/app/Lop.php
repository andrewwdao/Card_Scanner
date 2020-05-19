<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class Lop extends Model
{
    //
    protected $table = 'lops';
    protected $fillable=['id','malop','tenlop'];
    public $timestamps=true;
    public function lop()
    {
    	return $this->hasMany('App\SinhVien');
    }
}
