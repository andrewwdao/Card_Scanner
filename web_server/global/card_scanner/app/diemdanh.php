<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class diemdanh extends Model
{
	
    protected $table='diemdanhs';
    protected $fillable=['masv','mamon','buoivang','mathe'];
    
    public $timestamps=true;
}
