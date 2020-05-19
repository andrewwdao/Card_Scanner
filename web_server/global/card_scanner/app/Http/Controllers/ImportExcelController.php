<?php

namespace App\Http\Controllers;

use Illuminate\Http\Request;
use App\Http\Controllers\Controller;
use App\Imports\UsersImport;

class ImportExcelController extends Controller
{
    public function postImport(Request $request){
        Excel::import(new UsersImport, $request->file('import-list'));

        return back()->with('Message','Dữ liệu được nhập thành công!');
    }
}
