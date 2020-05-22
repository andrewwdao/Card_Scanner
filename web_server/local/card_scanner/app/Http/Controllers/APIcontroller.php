<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use App\diemdanh;
use App\SinhVien;
use App\monhoc;
use Illuminate\Support\Carbon;
use Log;

class APIcontroller extends Controller
{
    //Funcion Checkin
    public function getCheckin(){
        return "Không có quyền truy cập hệ thống điểm danh";
    }
    public function postCheckin(Request $request){
        //echo response($request);
        if(!$request->hasFile('file'))
        {
            $diemdanh =  diemdanh::create(['masv' => $request->mssv,'mamon'=>$request->mamon,'buoivang'=>$request->timedd, 'mathe'=>$request->mathe]);
            if($diemdanh)
            {
                return  response()->json(["status" => 200, "Messages" => "Điểm danh thành công"]);
            }
            else
            {
                //return  response()->json(["status" => 400, "Messages" => "Điểm danh thất bại"]);
                return  response()->json(["Messages" => "Điểm danh thất bại"],400);
            }
        }
        else
        {
            $dumps = [];
            //$content = file($request->file);
            //$content = [];
            $content = file($request->file('file'));
            foreach($content as $val)
            {
                $temps = str_replace("\r\n","",explode("|", $val));
                $dumps[] = array("masv" => $temps[0], "mamon" =>$temps[1], "buoivang" => $temps[2]);
            }
            // dd($dumps);
            foreach($dumps as $diemdanh)
            {
                try{
                    diemdanh::insert($diemdanh);
                }
                catch(\Exception $e){
                }
            }
            //return Response::json(array("message" => "Điểm danh thành công"), 200);
            //return response()->json(["status"=>200, "Messages"=>"Điểm danh file thành công!"]);
            //return response()->json($content,200);
            return response()->json($dumps,200);
            //return response()->json($request,200);
        }
    }
    public function getCheckinjs(){
        return "Không có quyền truy cập hệ thống điểm danh";
    }

    public function postCheckinjs(Request $request){
        
        $data = $request->json()->all();

        $dumps = [];
        foreach ($data as $key => $value) {
            $dumps[] = array("mssv" => $data[$key]['m'], "ma_mon" => $data[$key]['c'], "ngay" => $data[$key]['d']);

            $id_mon = monhoc::where('ma_mon', $data[$key]['c'])->get()[0]['id'];

            $id_sinhvien = SinhVien::where('mssv', $data[$key]['m'])->where('id_mon', $id_mon)->get()[0]['id'];
        
            diemdanh::insert([
                'id_sinhvien' => $id_sinhvien,
                'id_mon' => $id_mon,
                'thoi_gian' => $data[$key]['d']
            ]);
        }

        // Reference
        // foreach ($dumps as $key => $value) {
        //     try {
        //         diemdanh::insert($value);
        //     } 
        //     catch (\Exception $e) {
        //         echo $e;
        //     }
        // }

        // return response("NAT",200);
        return response()->json($dumps, 200);
    }
    
    //requestDataSV
    public function RequestSV(Request $request){
        //nonunicode
        function vn_to_str($str){
 
            $unicode = array(
             
            'a'=>'á|à|ả|ã|ạ|ă|ắ|ặ|ằ|ẳ|ẵ|â|ấ|ầ|ẩ|ẫ|ậ',
             
            'd'=>'đ',
             
            'e'=>'é|è|ẻ|ẽ|ẹ|ê|ế|ề|ể|ễ|ệ',
             
            'i'=>'í|ì|ỉ|ĩ|ị',
             
            'o'=>'ó|ò|ỏ|õ|ọ|ô|ố|ồ|ổ|ỗ|ộ|ơ|ớ|ờ|ở|ỡ|ợ',
             
            'u'=>'ú|ù|ủ|ũ|ụ|ư|ứ|ừ|ử|ữ|ự',
             
            'y'=>'ý|ỳ|ỷ|ỹ|ỵ',
             
            'A'=>'Á|À|Ả|Ã|Ạ|Ă|Ắ|Ặ|Ằ|Ẳ|Ẵ|Â|Ấ|Ầ|Ẩ|Ẫ|Ậ',
             
            'D'=>'Đ',
             
            'E'=>'É|È|Ẻ|Ẽ|Ẹ|Ê|Ế|Ề|Ể|Ễ|Ệ',
             
            'I'=>'Í|Ì|Ỉ|Ĩ|Ị',
             
            'O'=>'Ó|Ò|Ỏ|Õ|Ọ|Ô|Ố|Ồ|Ổ|Ỗ|Ộ|Ơ|Ớ|Ờ|Ở|Ỡ|Ợ',
             
            'U'=>'Ú|Ù|Ủ|Ũ|Ụ|Ư|Ứ|Ừ|Ử|Ữ|Ự',
             
            'Y'=>'Ý|Ỳ|Ỷ|Ỹ|Ỵ',
             
            );
             
            foreach($unicode as $nonUnicode => $uni){
             
            $str = preg_replace("/($uni)/i", $nonUnicode, $str);
             
            }

            $str = str_replace(' '.chr( 194 ) . chr( 160 ),'',$str);
            $str = str_replace(chr( 194 ) . chr( 160 ),'',$str);
            $str = str_replace(' ',' ',$str);
             
            return $str;
             
        }

        if($request->has('class'))
        {
            $data = SinhVien::where('id_mon', monhoc::where('ma_mon',$request->class)->get()[0]['id'])
                    ->get(['mssv','ho', 'ten']);
        }
        else{
            $data = SinhVien::get(['mssv','ho', 'ten']);
        }
        
        $temp = [];
        foreach ($data as $key => $value) {
            //$temp[] = array("mssv" => $value['mssv'], "name" => vn_to_str($value['hoten']), "class" => $value['malop']);
            $temp[] = array("m" => $value['mssv'], "n" => vn_to_str($value['ho'] . ' ' . $value['ten']));
        }

        return response()->json( $temp, 200);
    }

    //request class
    public function RequestClass(Request $request){
        if($request->has('new')){
            $data = monhoc::get(['ma_mon']);
        }
        else{
            $data = monhoc::get(['ma_mon']);
        }

        $temp = [];
        foreach($data as $key => $value){
            $temp[] = array("Class" => $value['ma_mon']);
        }

        return response()->json($temp, 200);
    }
}
