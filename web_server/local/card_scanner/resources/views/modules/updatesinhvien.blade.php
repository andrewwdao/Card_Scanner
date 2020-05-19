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
										<input type="text" class="form-control" disabled value="{{ $data->masv }}" >
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Tên sinh viên</label>
										<input type="text" class="form-control" value="{{ $data->hoten }}" name="hoten">
									</div>
								</div>
								<div class="col-lg-6">
										<div class="form-group">
											<label>Giới tính</label>
											<select name="gioitinh" id="" class="form-control">
												<option @if($data->gioitinh=='Nam') selected  @endif value="Nam">Nam</option>
												<option @if($data->gioitinh=='Nữ') selected  @endif value="Nữ">Nữ</option>
											</select>
										</div>
								</div>
								<div class="col-lg-6">
										<div class="form-group">
											<label>Lớp</label>
											<select name="malop" id="" class="form-control">
												@foreach($lop as $val)
												<option @if($data->malop==$val->malop) selected @endif value="{{ $val->malop }}">{{ $val->tenlop }}</option>
												
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