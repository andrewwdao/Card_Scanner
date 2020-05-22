<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreateDiemdanhsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('diemdanhs', function (Blueprint $table) {
            $table->string('masv',50);
            $table->string('mamon',50);
            $table->date('buoivang');
            $table->foreign('masv')
            ->references('masv')->on('sinh_viens')
            ->onDelete('cascade');
            $table->foreign('mamon')
            ->references('mamon')->on('monhoc')
            ->onDelete('cascade');
            $table->string('mathe',100)->nullable();
            $table->primary(['masv', 'mamon','buoivang']);
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('diemdanhs');
    }
}
