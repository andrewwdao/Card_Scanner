<?php

use Illuminate\Database\Seeder;

class DatabaseSeeder extends Seeder
{
    /**
     * Seed the application's database.
     */
    public function run()
    {
        $this->call('seedAdmin');
        // $this->call('seedlop');
        // $this->call('seedsinhvien');
    }
}
class seedAdmin extends Seeder
{
    public function run()
    {
        DB::table('admin')->insert([
            ['taikhoan' => 'admin', 'password' => bcrypt('123456')],
            // ['taikhoan' => 'nhuttran@natlabs.net', 'password' => bcrypt('Natlabs_397')],
            // ['taikhoan' => 'quangthong@natlabs.net', 'password' => bcrypt('Natlabs_482')],
            // ['taikhoan' => 'anhkhoi@natlabs.net', 'password' => bcrypt('123456')],
            // ['taikhoan' => 'minhan@natlabs.net', 'password' => bcrypt('123456')],
        ]);
    }
}


