<?php

use Illuminate\Support\Facades\Schema;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Database\Migrations\Migration;

class CreatemonhocTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('monhoc', function (Blueprint $table) {
            $table->increments('id');
            $table->string('mamon',50)->unique();
            $table->string('tenmon');
            $table->integer('sotinchi');
            $table->integer('sotiet');
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
        Schema::dropIfExists('monhoc');
    }
}
