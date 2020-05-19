<?php

namespace App\Exports;

use App\diemdanh;
use App\SinhVien;
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
        $this->malop = $malop;
        $this->mamon = $mamon;
    }

    public function query()
    {
        $listSinhvien = SinhVien::where('malop', $this->malop)->pluck('masv')->toArray();
        $data = diemdanh::select('diemdanhs.mamon', 'diemdanhs.masv', \DB::raw('count(diemdanhs.masv) as buoivang'), \DB::raw('sinh_viens.hoten as tensv'))->join('sinh_viens','diemdanhs.masv', '=', 'sinh_viens.masv' )->where('diemdanhs.mamon', $this->mamon)->whereIn('diemdanhs.masv',$listSinhvien)->orderBy('diemdanhs.masv', 'asc')->groupBy(['diemdanhs.masv', 'diemdanhs.mamon', 'sinh_viens.hoten']);
        return $data;
    }
    public function headings(): array
    {
        return [
            "MSSV",
            "Họ tên SV",
            "Mã môn",
            "Số buổi điểm danh",
        ];
    }
    public function map($invoice): array
    {
        return [
           
            $invoice->masv,
            $invoice->tensv,
            $invoice->mamon,
            $invoice->buoivang,
        ];
    }

    public function columnFormats(): array
    {
        return [
          
        ];
    }
}