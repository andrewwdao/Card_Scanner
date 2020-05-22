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
							<input type="hidden" name="_token" value="{{csrf_token()}}">
							<div class="row">
								<div class="col-lg-6">
									<div class="form-group">
										<label>Mã môn</label>
										<input type="text" maxlength="5" class="form-control" placeholder="Nhập mã môn..." name="ma_mon" value="{{old('ma_mon')}}">
										<p class="text-danger">{{$errors->first('ma_mon')}}</p>
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Tên môn</label>
										<input type="text" class="form-control" placeholder="Nhập tên môn..." name="ten_mon" value="{{old('ten_mon')}}">
										<p class="text-danger">{{$errors->first('ten_mon')}}</p>
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Học kỳ</label>
										<input maxlength=1 type="text" class="form-control" placeholder="Học kỳ..." name="hoc_ky" value="{{old('hoc_ky')}}">
										<p class="text-danger">{{$errors->first('hoc_ky')}}</p>
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Năm học</label>
										<input maxlength=9 type="text" class="form-control" placeholder="Năm học..." name="nam_hoc" value="{{old('nam_hoc')}}">
										<p class="text-danger">{{$errors->first('nam_hoc')}}</p>
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Buổi</label>
										<input type="text" maxlength="2" class="form-control" placeholder="Nhập buổi..." name="buoi" value="{{old('buoi')}}">
										<p class="text-danger">{{$errors->first('buoi')}}</p>
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Số buổi</label>
										<input type="text" maxlength="3" class="form-control" placeholder="Nhập buổi..." name="so_buoi" value="{{old('so_buoi')}}">
										<p class="text-danger">{{$errors->first('so_buoi')}}</p>
									</div>
								</div>
							</div>
							<div class="text-right">
								<button class="btn btn-primary"><i class="fe fe-arrow-down-circle"></i> Thêm môn</button>
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
										<th>Mã môn</th>
										<th>Tên môn</th>
										<th>Số buổi</th>
										<th class="text-right">Chức năng</th>
									</tr>
								</thead>
								<tbody>
									@foreach($mh as $key=>$val)
									<tr>
										<td>{{$key+1}}</td>
										<td hidden class='id'>{{$val->id}}</td>
										<td>{{$val->ma_mon}}</td>
										<td>{{$val->ten_mon}}</td>
										<td>{{$val->so_buoi}}</td>
										<td class="text-right">
											<a href="{{route('gupdatemh',$val->id)}}" class="btn btn-warning" id="edit"><i class="fe fe-edit"></i></a>
											<button class="btn btn-danger delete"><i class="fe fe-trash"></i></button>
										</td>
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

<script>
	
		$('.delete').click(function (e) { 
			var t=$(this).closest('tr').find('.id').text()
			$.ajax({
				type: "post",
				url: "{{route('ajax_delete_monhoc')}}",
				data: {
					'_token':"{{csrf_token()}}",
					'id':t
				},
	
				success: function (response) {
					response=='ok'? location.reload():''
				}
			});
			
		});
  
</script>
@endsection