@extends('masterlayout')
@section('content')
<div id="content" class="page-main">
	<div class="container-fluid">
		<div class="row">
			<div class="col-lg-12">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<div class="col-md-6"><h3 class="card-title text-uppercase">Danh sách sinh viên được train khuôn mặt</h3></div>
						
					</div>
					<div class="card-body">
						@if(session()->has('mes'))
						<div class="alert alert-icon alert-success" role="alert">
 						 <i class="fe fe-bell mr-2" aria-hidden="true"></i> {{session()->get('mes')}}
						</div>
						
						@endif
						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>STT</th>
										<th>MSSV</th>
										<th>Tên sinh viên</th>
										<th>Giới tính</th>
										{{--<th>Lớp</th> --}}
										<th class="text-right">Chức năng</th>
									</tr>
								</thead>
								<tbody>
									@forelse($data as $key=>$val)
									<tr>
										<td>{{$key+1}}</td>
										
									
										<td>{{$val->masv}}</td>
										<td>{{$val->hoten}}</td>
										<td>{{ $val->gioitinh }}</td>
										<td class="text-right">
											
											<a href="{{route('delface',[$val->masv])}}" class="btn btn-danger delete"><i class="fe fe-trash"></i> Xóa</a>
										</td>
									</tr>
									@empty

									@endforelse
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
	
</script>
@endsection