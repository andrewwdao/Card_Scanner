<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class diemdanh extends Model
{
    protected $table='diemdanh';
    protected $fillable=['id_sv','id_mon', 'thoi_gian'];
    
    public $timestamps=false;
}
