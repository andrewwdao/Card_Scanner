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
							{{-- <div class="form-group">
								<div class="custom-file">
									<input type="file" class="custom-file-input" multiple>
									<label class="custom-file-label">Nạp file Excel</label>
								</div>
							</div> --}}
							<div class="row">
								<div class="col-lg-6">
									<div class="form-group">
										<label>Mã lớp</label>
										<input type="text" class="form-control" placeholder="Nhập mã lớp..." name="malop">
										<p class="text-danger">{{$errors->first('malop')}}</p>
									</div>
								</div>
								<div class="col-lg-6">
										<div class="form-group">
											<label>Tên lớp</label>
											<input type="text" class="form-control" placeholder="Nhập tên lớp..." name="tenlop">
											<p class="text-danger">{{$errors->first('tenlop')}}</p>
										</div>
								</div>
							</div>
							<div class="text-right">
								<button class="btn btn-primary"><i class="fe fe-arrow-down-circle"></i> Thêm danh sách lớp</button>
							</div>
						</form>
					</div>
				</div>
			</div>
			<div class="col-lg-12">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title text-uppercase">Danh sách lớp</h3>
					</div>
					<div class="card-body">
						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>STT</th>
										<th>Mã lớp</th>
										<th >Tên lớp</th>
										<th class="text-right">Chức năng</th>
									</tr>
								</thead>
								<tbody>
									@foreach($lop as $key=>$val)
									<tr>
										<td>{{$key+1}}</td>
										<td hidden class="id">{{ $val->id }}</td>
										<td>{{$val->malop}}</td>
										<td>{{$val->tenlop}}</td>
										<td class="text-right">
											<a href="{{ route('update-lop',$val->id) }}" class="btn btn-warning"><i class="fe fe-edit"></i></a>
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
		//require(['jquery'],function(){
		$('.delete').click(function (e) { 
			
			var t=$(this).closest('tr').find('.id').text()
			if(confirm("Không thể hoàn tác, Đồng ý xóa?"))
			{
				$.ajax({
					type: "post",
					url: "{{route('destroylop')}}",
					data: {
						'_token':"{{csrf_token()}}",
						'id':t
					},
		
					success: function (response) {
						response=='ok'? location.reload():''
					}
				});
			}
		
			
		});
   // });
</script>
@endsection