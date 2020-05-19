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
										<input type="text" class="form-control" placeholder="Nhập mã môn..." name="mamon" value="{{old('mamon')}}">
										<p class="text-danger">{{$errors->first('mamon')}}</p>
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Tên môn</label>
										<input type="text" class="form-control" placeholder="Nhập tên môn..." name="tenmon" value="{{old('tenmon')}}">
										<p class="text-danger">{{$errors->first('tenmon')}}</p>
									</div>
								</div>
							</div>
							<div class="row">
								<div class="col-lg-6">
									<div class="form-group">
										<label>Số tín chỉ</label>
										<input type="text" class="form-control" placeholder="Nhập số tín chỉ..." name="sotinchi" value="{{old('sotinchi')}}">
										<p class="text-danger">{{$errors->first('sotinchi')}}</p>
									</div>
								</div>
								<div class="col-lg-6">
									<div class="form-group">
										<label>Số tiết</label>
										<input type="text" class="form-control" placeholder="Nhập số tiết..." name="sotiet" value="{{old('sotiet')}}">
										<p class="text-danger">{{$errors->first('sotiet')}}</p>
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
										<th>Môn học</th>
										<th>Mã môn</th>
										<th>Số tín chỉ</th>
										<th>Số tiết</th>
										<th class="text-right">Chức năng</th>
									</tr>
								</thead>
								<tbody>
									@foreach($mh as $key=>$val)
									<tr>
										<td>{{$key+1}}</td>
										<td hidden class='id'>{{$val->id}}</td>
										<td>{{$val->tenmon}}</td>
										<td>{{$val->mamon}}</td>
										<td>{{$val->sotinchi}}</td>
										<td>{{$val->sotiet}}</td>
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