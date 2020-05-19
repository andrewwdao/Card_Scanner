@extends('masterlayout')
@section('content')
<div id="content" class="page-main">
	<div class="container-fluid">
		<div class="row">
			<div class="col-lg-12">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title text-uppercase">Sửa Thông Tin Môn Học</h3>
					</div>
					<div class="card-body">
						<form action="" method="post">
							<input type="hidden" name="_token" value="{{csrf_token()}}">
							<div class="row">
								<div class="col-lg-6">
									<div class="form-group">
										<label>Tên môn</label>
									<input type="text" class="form-control" placeholder="Nhập tên môn..." name="tenmon" value="{{$up->tenmon}}">
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Số tín chỉ</label>
										<input type="text" class="form-control" placeholder="Nhập số tín chỉ..." name="sotinchi" value="{{$up->sotinchi}}">
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Số tiết</label>
									<input type="text" class="form-control" placeholder="Nhập số tiết..." name="sotiet" value="{{$up->sotiet}}">
									</div>
								</div>
							</div>
							<div class="text-right">
								<button class="btn btn-primary"><i class="fe fe-arrow-down-circle"></i> Cập nhật</button>
							</div>
						</form>
					</div>
				</div>
			</div>
			<div class="col-lg-12">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title text-uppercase">Danh sách môn học</h3>
					</div>
					<div class="card-body">
						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>STT</th>
										<th>Môn học</th>
										<th>Số tín chỉ</th>
										<th>Số tiết</th>
										{{-- <th class="text-right">Chức năng</th> --}}
									</tr>
								</thead>
								<tbody>
									@foreach($mh as $key=>$val)
									<tr>
										<td>{{$key+1}}</td>
										<td>{{$val->tenmon}}</td>
										<td>{{$val->sotinchi}}</td>
										<td>{{$val->sotiet}}</td>
									</tr>
									@endforeach

								</tbody>
							</table>
						</div>
					</div>
				</div>
			</div>
		</div>
	</div>
</div>
@endsection