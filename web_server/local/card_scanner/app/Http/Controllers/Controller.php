<?php

namespace App\Http\Controllers;

use Illuminate\Foundation\Bus\DispatchesJobs;
use Illuminate\Routing\Controller as BaseController;
use Illuminate\Foundation\Validation\ValidatesRequests;
use Illuminate\Foundation\Auth\Access\AuthorizesRequests;
use Illuminate\Http\Request;
use App\Http\Requests\MonhocRequest;
use App\Http\Requests\LoginRequest;
use App\Http\Requests\LopRequest;
use Auth;
use App\monhoc;
use App\Lop;
use App\SinhVien;
use App\Classes\My_Face;
use Illuminate\Support\Carbon;
use DB;
use App\diemdanh;
use DateTime;
use App\Exports\CheckinExport;
use App\Imports\UsersImport;
use Maatwebsite\Excel\Facades\Excel;

class Controller extends BaseController
{
    use AuthorizesRequests, DispatchesJobs, ValidatesRequests;

    public function index()
    {
        $dsmon = monhoc::all();

        return view('modules.indexcontent', compact('dsmon'));
    }

    public function glogin()
    {
        if (Auth::guard('admin')->check()) {
            return redirect()->route('trang-chu');
        } else {
            return view('login');
        }
    }

    public function GetDanhsachsinhvien(Request $request)
    {
        if ($request->ajax()) {
            $dssinhvien = SinhVien::where('malop', $request->get('malop'))->get();
            $tenlop = Lop::where('malop', $request->get('malop'))->pluck('tenlop');
            $ds = '';
            foreach ($dssinhvien as $sinhvien) {
                $ds .= '<tr>
                <td>'.$sinhvien->masv.'</td>
                <td>'.$sinhvien->hoten.'</td>
                <td class="text-right">
                    <a href="'.route('training', [$sinhvien->masv]).'" class="btn btn-warning"><i class="fe fe-gitlab"></i> Train Now</a>
                </td>
            </tr>';
            }

            return array('ds' => $ds, 'tenlop' => $tenlop);
        }
    }

    public function plogin(LoginRequest $request)
    {
        // return $request->all();
        $auth = array('taikhoan' => $request->taikhoan, 'password' => $request->matkhau);
        if (Auth::guard('admin')->attempt($auth, false)) {
            return redirect()->route('trang-chu');
        } else {
            return redirect()->back()->with(['errormessage' => 'Email hoặc password không đúng!']);
        }
    }


    public function logout()
    {
        Auth::guard('admin')->logout();

        return redirect()->route('gdang-nhap');
    }


    public function Diem_danh(Request $request){
      if($request->ajax())
      {
        
        if($request->has('fileanh'))
        {
            // $today = Carbon::today()->toDateString();
            // $dmm = new My_Face();

            // $data = $dmm->recognize($request->file('fileanh'));
            // if(isset($data->Errors))
            // {
            //     return response()->json(['Error' => 'Không có bất kì ảnh nào trong hệ thống ']);
            // }

            if(isset($data) && $request->get('monhoc') != '')
            {
                foreach($data as $val)
                {
                    foreach($val as $lol)
                    {
                        // dd($lol->transaction->status);
                       if($lol->transaction->status === 'success')
                       {
                           try 
                            {
                                diemdanh::create([
                                    'mssv' => $lol->transaction->subject_id,
                                    'ma_mon'=> monhoc::where('ma_mon',substr($row[5],0,5))->where('buoi',substr($row[5],6,2))->first(),
                                    'buoivang'=>$today
                                ]);
                            }
                            catch(\Illuminate\Database\QueryException $e){
                                echo $e;
                            }
                           

                       }
                    }
                }

                return response()->json($data);

            }
        }
      }
    }

    public function GetquanLyMonHoc()
    {
        $mh = monhoc::all();

        return view('modules.quanlymonhoc', compact('mh'));
    }

    public function PostquanLyMonHoc(MonhocRequest $request)
    {
        monhoc::insert([
            'ma_mon' => $request->ma_mon . '-' . $request->buoi,
            'ten_mon' => $request->ten_mon,
            // 'so_tin_chi' => $request->so_tin_chi,
            // 'so_tiet' => $request->so_tiet,
            'hoc_ky' => $request->hoc_ky,
            'nam_hoc' => $request->nam_hoc,
            'so_buoi' => $request->so_buoi,
        ]);

        return redirect()->route('gquan-ly-mon-hoc')->with(['message' => 'Thêm thành công!']);
    }

    public function Postupdatemonhoc(MonhocRequest $request, $id)
    {
        monhoc::find($id)->update([
            'ma_mon' => $request->ma_mon . '-' . $request->buoi,
            'ten_mon' => $request->ten_mon,
            // 'so_tin_chi' => $request->so_tin_chi,
            // 'so_tiet' => $request->so_tiet,
            'hoc_ky' => $request->hoc_ky,
            'nam_hoc' => $request->nam_hoc,
            'so_buoi' => $request->so_buoi,
        ]);

        return redirect()->route('gquan-ly-mon-hoc');
    }

    public function Getupdatemonhoc($id)
    {
        $mh = monhoc::all();
        $up = monhoc::find($id);
        if ($up) {
            return view('modules.updatemonhoc', compact('mh', 'up'));
        } else {
            return redirect()->route('gquan-ly-mon-hoc');
        }
    }

    public function Delete_monhoc(Request $request)
    {
        if ($request->ajax()) {
            if (monhoc::find($request->id)->delete()) {
                SinhVien::where('id_mon', $request->id)->delete();
                diemdanh::where('id_mon', $request->id)->delete();
                return 'ok';
            } else {
                return 'error';
            }
        }
    }

    public function GetquanLyLop()
    {
        $lop = Lop::all();
        $mh = monhoc::all();

        return view('modules.quanlylop', compact('lop', 'mh'));
    }

    public function PostquanLyLop(LopRequest $request)
    {
        Lop::insert([
            'malop' => $request->mamon,
            'tenlop' => $request->tenlop,
        ]);

        return redirect()->route('gquan-ly-lop')->with(['message' => 'Thêm thành công!']);
    }

     public function quanLySinhVien(Request $request){
        if($request->get('query') && $request->get('query')!='')
        {
            $sinhvien=SinhVien::where('id_mon',$request->get('query'))->get();
            $query=$request->get('query');
        }
        else{
            $sinhvien=SinhVien::all();
            $query='';
        }
        $mh = monhoc::all();
        return view('modules.quanlysinhvien',compact('sinhvien','mh','query'));
    }

    public function destroy_sinhvien(Request $request)
    {
        if($request->ajax())
        {
            SinhVien::find($request->id)->delete();
            return 'ok';
        }
       

    }

    public function quanLyLop()
    {
    }

    public function quanLyDiemDanh(Request $request){
        if($request->has('export'))
        {
            return (new CheckinExport($request->lop, $request->mon))->download('diemdanh.xlsx');
        }

        if($request->get('id_mon')!=''){
            $data=SinhVien::join('diemdanh','sinhvien.id','=','id_sinhvien', 'left outer')
            ->join('monhoc', 'monhoc.id', '=', 'diemdanh.id_mon', 'left outer')
            ->where('monhoc.id', '=', $request->get('id_mon'))
            ->orderBy('mssv')
            ->select('mssv', 'ho', 'ten', 'so_buoi', 'ma_mon', DB::raw('count(*) as buoi_co_mat'))
            ->groupBy('mssv', 'ho', 'ten', 'so_buoi', 'ma_mon')->get();
            // ->join('monhoc', 'monhoc.id', '=', 'diemdanh.id_mon')
            // ->where('monhoc.id', $request->get('ma_mon'))
            // ->select('diemdanh.mssv','ho', 'ten', DB::raw('count(*) as buoi_co_mat'))
            // ->groupBy('diemdanh.mssv', 'ho', 'ten')->get();
            // $data = SinhVien::all();
        }
        else
        {
            $data=[];
        }
        $monhoc=monhoc::all();

        //dd($data);
        return view('modules.danhsachdiemdanh',compact('monhoc','data'));
    }
    public function chiTietBuoiVang($masv,$mon){
        $data=diemdanh::join('sinh_viens','diemdanhs.masv','=','sinh_viens.masv')->where('diemdanhs.masv',$masv)->where('mamon',$mon)->get();
        if(count($data)>0)
        {
            return view('modules.chitietbuoivang',compact('data'));
        }
        else{
            return redirect()->route('quan-ly-diem-danh');
        }
  
    }
    public function Post_themsinhvien(Request $request){
        // try{
        //     SinhVien::create($request->all());
        //     return redirect()->back();
        // }
        // catch(\Illuminate\Database\QueryException $ex){
        //     //
        // }
        try{
            if($request->has('Form1'))
            {
                // SinhVien::create($request->all());
                // return redirect()->back();
                $id_mon = monhoc::find($request->id_mon)->id;
                SinhVien::insert([
                    'mssv' => $request->mssv,
                    'ho' => $request->ho,
                    'ten' => $request->ten,
                    'gioi_tinh' => $request->gioi_tinh,
                    'id_mon' => $id_mon,
                ]);

                $sinhvien = SinhVien::all();
                
                // echo '<script> console.log(' . SinhVien::where('mssv', $request->mssv)->where('id_mon', $id_mon)->get()[0]['id'] . ')</script>';
                diemdanh::insert([
                    'id_sinhvien' => SinhVien::where('mssv', $request->mssv)
                                     ->where('id_mon', $id_mon)
                                     ->get()[0]['id'],
                    'id_mon' => $id_mon
                ]);
        
                return redirect()->route('quan-ly-sinh-vien')->with(['message' => 'Thêm thành công!']);
            }
            elseif($request->has('Form2'))
            {
                Excel::import(new UsersImport, $request->file('import-list'));

                return redirect()->back()->with('Message','Dữ liệu được nhập thành công, hãy kiểm tra lại!');
            }
            else
            {
                return redirect()->route('quan-ly-sinh-vien');
            }
        }
        catch(\Illuminate\Database\QueryException $ex){
            echo $ex;
        }
        
    }
    public function UpdateSinhVien($id)
    {
        $data=SinhVien::find($id);
        if($data)
        {
            $mh=monhoc::all();
            return view('modules.updatesinhvien',compact('data','mh'));
        }
        else
        {
            return redirect()->route('quan-ly-sinh-vien');
        }
    }

    public function PostUpdateSinhVien(Request $request,$id){
        SinhVien::find($id)->update([
            'mssv' => $request->mssv,
            'ho' => $request->ho,
            'ten' => $request->ten,
            'gioi_tinh' => $request->gioi_tinh,
            'id_mon' => monhoc::find($request->id_mon)->id,
        ]);
        return redirect()->route('quan-ly-sinh-vien');
    }
    public function destroy_lop(Request $request){
        if($request->ajax()){
            if(Lop::find($request->id)->delete())
                return 'ok';
            else
                return 'error';
            
        }
    }
    public function update_lop($id){
        $data=Lop::find($id);
        return view('modules.updatelop',compact('data'));
    }
    public function post_update_lop(Request $request,$id){
        Lop::find($id)->update([
            'tenlop'=>$request->tenlop
        ]);
        return redirect()->route('gquan-ly-lop');
    }
    public function Destroy_diemdanh(Request $request){
        if($request->ajax())
        {
            $newDate = date("Y-m-d", strtotime($request->buoivang));
            // return $newDate;
            $dd=diemdanh::where('masv',$request->masv)->where('mamon',$request->mamon)->whereDate('buoivang', $newDate)->delete();
     
            if($dd)
                return 'ok';
            else
                return 'error';
        }
    }
    
}
