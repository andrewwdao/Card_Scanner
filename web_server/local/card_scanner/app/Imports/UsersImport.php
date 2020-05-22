<?php

namespace App\Imports;

use App\SinhVien;
use App\monhoc;
use Maatwebsite\Excel\Concerns\ToModel;

class UsersImport implements ToModel
{
    /**
    * @param array $row
    *
    * @return \Illuminate\Database\Eloquent\Model|null
    */
    public function model( $row)
    {
        return new SinhVien([
            'mssv' => $row[1],
            'ho' => $row[2],
            'ten' => $row[3],
            'gioi_tinh' => strtolower($row[4]) == 'nam' ? 1 : 0,
            'id_mon' => monhoc::where('ma_mon', $row[5])->get()[0]['id'],
            //add data
        ]);
    }
}
