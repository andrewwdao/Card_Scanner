<?php


/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

use App\Classes\My_Face;

// Route::get('/test', function () {
//     $a = new My_Face();
//     dd($a->listall());
//     // dd($a->recognize('https://scontent.fvca1-1.fna.fbcdn.net/v/t1.0-9/11880378_500406640123413_6897335525622665309_n.jpg?_nc_cat=0&oh=ce4a397cbd8477c9f8d802d006f16034&oe=5B7C104C'));
// });
Route::get(
    '/',
    [
    'as' => 'gdang-nhap',
    'uses' => 'Controller@glogin',
]
);
Route::post('/', ['as' => 'pdang-nhap', 'uses' => 'Controller@plogin']);
Route::get('logout', ['as' => 'logout', 'uses' => 'Controller@logout']);

Route::group(['prefix' => 'quan-ly', 'middleware' => ['checkAdmin']], function () {
    Route::get(
        'trang-chu',
        [
        'as' => 'trang-chu',
        'uses' => 'Controller@quanLyDiemDanh',
    ]
    );

    Route::get(
        'training-list',
        [
    'as' => 'training-list',
    'uses' => 'Controller@trainingList',
    ]
    );
    Route::get(
            'training/{id}',
            [
    'as' => 'training',
    'uses' => 'Controller@training',
    ]
    );

    Route::get('get-ds-lop', ['as' => 'ds_sinhvien_lop', 'uses' => 'Controller@GetDanhsachsinhvien']);


     Route::get('quan-ly-diem-danh', ['as' => 'quan-ly-diem-danh', 'uses' => 'Controller@quanLyDiemDanh']);
     Route::get('chi-tiet-buoi-vang/{masv}/{mon}', ['as' => 'chi-tiet-buoi-vang', 'uses' => 'Controller@chiTietBuoiVang']);

    Route::get('quan-ly-mon-hoc', ['as' => 'gquan-ly-mon-hoc', 'uses' => 'Controller@GetquanLyMonHoc']);
    Route::post('quan-ly-mon-hoc', ['as' => 'pquan-ly-mon-hoc', 'uses' => 'Controller@PostquanLyMonHoc']);
    Route::get('updatemonhoc/{id}', ['as' => 'gupdatemh', 'uses' => 'Controller@Getupdatemonhoc']);
    Route::post('updatemonhoc/{id}', ['as' => 'pupdatemh', 'uses' => 'Controller@Postupdatemonhoc']);

        Route::get('quan-ly-mon-hoc',['as'=>'gquan-ly-mon-hoc','uses'=>'Controller@GetquanLyMonHoc']);
        Route::post('quan-ly-mon-hoc',['as'=>'pquan-ly-mon-hoc','uses'=>'Controller@PostquanLyMonHoc']);
        Route::get('updatemonhoc/{id}',['as'=>'gupdatemh','uses'=>'Controller@Getupdatemonhoc']);
        Route::post('updatemonhoc/{id}',['as'=>'pupdatemh','uses'=>'Controller@Postupdatemonhoc']);

 
        Route::get('quan-ly-lop',['as'=>'gquan-ly-lop','uses'=>'Controller@GetquanLylop']);
        Route::post('quan-ly-lop',['as'=>'pquan-ly-lop','uses'=>'Controller@PostquanLylop']);

        Route::get('quan-ly-khuon-mat',['as'=>'qlkhuonmat','uses'=>'Controller@quanLyKhuonMat']);
        Route::get('delete_face/{id}',['as'=>'delface','uses'=>'Controller@DeleteKhuonMat']);


        Route::get('quan-ly-sinh-vien',['as'=>'quan-ly-sinh-vien','uses'=>'Controller@quanLySinhVien']);
        Route::post('quan-ly-sinh-vien',['as'=>'quan-ly-sinh-vien','uses'=>'Controller@Post_themsinhvien']);
        Route::get('update-sinh-vien/{id}',['as'=>'update-sinh-vien','uses'=>'Controller@UpdateSinhVien']);
        Route::post('update-sinh-vien/{id}',['as'=>'update-sinh-vien','uses'=>'Controller@PostUpdateSinhVien']);
        Route::get('update-lop/{id}',['as'=>'update-lop','uses'=>'Controller@update_lop']);
        Route::post('update-lop/{id}',['as'=>'update-lop','uses'=>'Controller@post_update_lop']);
        Route::get('sinhvien','Controller@quanLySinhVien');

        //route ajax
        Route::post('ajaxdeletemonhoc',['as'=>'ajax_delete_monhoc','uses'=>'Controller@Delete_monhoc']);
        Route::post('destroy_sinhvien',['as'=>'destroysinhvien','uses'=>'Controller@destroy_sinhvien']);
        Route::post('destroy_lop',['as'=>'destroylop','uses'=>'Controller@destroy_lop']);
        Route::post('train_data_image/{id}', ['as' => 'traindata', 'uses' => 'Controller@Train_data_image']);
        Route::post('diem-danh',['as' => 'diemdanh', 'uses' => 'Controller@Diem_danh']);
        Route::post('Destroy_diemdanh',['as'=>'Destroy_diemdanh','uses'=>'Controller@Destroy_diemdanh']);
    //Route::get('quan-ly-lop',['as'=>'quan-ly-lop','uses'=>'Controller@quanLylop']);
        Route::post('import-excel-data',['as'=>'import-excel-data','uses'=>'ImportExcelController@postImport']);

});
