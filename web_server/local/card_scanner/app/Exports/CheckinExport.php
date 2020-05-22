<?php

namespace App\Exports;
use DB;

use App\diemdanh;
use App\SinhVien;
use App\monhoc;
use Maatwebsite\Excel\Concerns\FromQuery;
use Maatwebsite\Excel\Concerns\Exportable;
use PhpOffice\PhpSpreadsheet\Style\NumberFormat;
use Maatwebsite\Excel\Concerns\WithColumnFormatting;
use Maatwebsite\Excel\Concerns\WithMapping;
use Maatwebsite\Excel\Concerns\WithHeadings;

class CheckinExport implements FromQuery, WithColumnFormatting, WithMapping,  WithHeadings
{
    use Exportable;

    public function __construct($malop, $mamon)
    {
        $this->mamon = $mamon;
    }

    public function query()
    {
        // $listSinhvien = SinhVien::where('malop', $this->malop)->pluck('masv')->toArray();
        // $data = diemdanh::select('diemdanhs.mamon', 'diemdanhs.masv', \DB::raw('count(diemdanhs.masv) as buoivang'), \DB::raw('sinh_viens.hoten as tensv'))->join('sinh_viens','diemdanhs.masv', '=', 'sinh_viens.masv' )->where('diemdanhs.mamon', $this->mamon)->whereIn('diemdanhs.masv',$listSinhvien)->orderBy('diemdanhs.masv', 'asc')->groupBy(['diemdanhs.masv', 'diemdanhs.mamon', 'sinh_viens.hoten']);
        $data=SinhVien::join('diemdanh','sinhvien.id','=','diemdanh.id_sinhvien')
        ->join('monhoc', 'monhoc.id', '=', 'diemdanh.id_mon')
        ->select('mssv', 'ho', 'ten', 'ma_mon', 'ten_mon', 'hoc_ky', 'nam_hoc', 'so_buoi', DB::raw('count(*) as buoi_co_mat'))
        ->groupBy('mssv', 'ho', 'ten', 'ma_mon', 'ten_mon', 'hoc_ky', 'nam_hoc', 'so_buoi');
        return $data;
    }

    public function headings(): array
    {
        return [
            "MSSV",
            "Họ",
            "Tên",
            "Mã môn",
            "Tên môn",
            "Học kỳ",
            "Năm học",
            "Số buổi có mặt",
            "Tổng số buổi",
        ];
    }

    public function map($invoice): array
    {
        return [
            $invoice->mssv,
            $invoice->ho,
            $invoice->ten,
            $invoice->ma_mon,
            $invoice->ten_mon,
            $invoice->hoc_ky,
            $invoice->nam_hoc,
            (string)((int)($invoice->buoi_co_mat-1)),
            $invoice->so_buoi,
        ];
    }

    public function columnFormats(): array
    {
        return [
          
        ];
    }
}