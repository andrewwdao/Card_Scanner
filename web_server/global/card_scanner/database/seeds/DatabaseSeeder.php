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
        ]);
    }
}


