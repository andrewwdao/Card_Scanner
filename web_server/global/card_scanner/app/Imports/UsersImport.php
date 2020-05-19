<?php

namespace App\Imports;

use App\SinhVien;
use Maatwebsite\Excel\Concerns\ToModel;

class UsersImport implements ToModel
{
    /**
    * @param array $row
    *
    * @return \Illuminate\Database\Eloquent\Model|null
    */
    public function model(array $row)
    {
        return new SinhVien([
            'masv' => $row[1],
            'hoten' => $row[2],
            'gioitinh' => $row[3],
            'malop' => $row[4]
            //add data
        ]);
    }
}
