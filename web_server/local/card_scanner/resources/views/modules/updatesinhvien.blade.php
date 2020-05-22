@extends('masterlayout')
@section('content')
<div id="content" class="page-main">
	<div class="container-fluid">
		<div class="row">
			<div class="col-lg-12">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title text-uppercase">Thao tác</h3>
					</div>
					<div class="card-body">
						<form action="" method="post">
						<input type="hidden" name="_token" value="{{ csrf_token() }}">
							<div class="row">
								<div class="col-lg-6">
									<div class="form-group">
										<label>Mã sinh viên</label>
										<input maxlength=8 type="text" class="form-control" placeholder="Nhập mã sinh viên..." name="mssv" value={{$data->mssv}}>
									</div>
								</div>
								<div class="col-lg-6">
										<div class="form-group">
											<label>Giới tính</label>
											<select name="gioi_tinh" id="" class="form-control">
												<option @if($data->gioi_tinh=='1') selected  @endif value="Nam">Nam</option>
												<option @if($data->gioi_tinh=='0') selected  @endif value="Nữ">Nữ</option>
											</select>
										</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Họ sinh viên</label>
										<input maxlength=50 type="text" class="form-control" placeholder="Nhập họ sinh viên..." name="ho" value={{$data->ho}}>
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Tên sinh viên</label>
										<input maxlength=50 type="text" class="form-control" placeholder="Nhập tên sinh viên..." name="ten" value={{$data->ten}}>
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Lớp</label>
										<select name="id_mon" id="" class="form-control">
											@foreach($mh as $val)
											<option @if($data->id_mon == $val->id) selected @endif value="{{ $val->id }}">{{ $val->ma_mon }}</option>
											@endforeach
										</select>
									</div>
								</div>
							</div>
							<div class="text-right">
								<button class="btn btn-primary"><i class="fe fe-arrow-down-circle"></i> Chỉnh sửa</button>
							</div>
						</form>
					</div>
				</div>
			</div>
		</div>
	</div>
</div>
@endsection