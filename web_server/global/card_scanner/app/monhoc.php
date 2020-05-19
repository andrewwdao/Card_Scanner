<?php

namespace App;

use Illuminate\Database\Eloquent\Model;

class monhoc extends Model
{
    //
    protected $table = 'monhocs';
    protected $fillable=['id','mamon','tenmon','sotinchi','sotiet'];
	public $timestamps=true;
}
