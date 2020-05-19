<?php

use Illuminate\Http\Request;
use App\diemdanh;
use App\SinhVien;
use Illuminate\Support\Carbon;

/*
|--------------------------------------------------------------------------
| API Routes
|--------------------------------------------------------------------------
|
| Here is where you can register API routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| is assigned the "api" middleware group. Enjoy building your API!
|
*/
Route::get('checkin',['as'=>'checkin','uses'=>'APIcontroller@getCheckin']);
Route::post('checkin',['as'=>'checkin','uses'=>'APIcontroller@postCheckin']);
Route::get('checkinjs',['as'=>'checkin','uses'=>'APIcontroller@getCheckinjs']);
Route::post('checkinjs',['as'=>'checkin','uses'=>'APIcontroller@postCheckinjs']);
Route::get('requestSV',['as'=>'requestSV','uses'=>'APIcontroller@RequestSV']);
Route::get('requestClass',['as'=>'requestClass','uses'=>'APIcontroller@RequestClass']);