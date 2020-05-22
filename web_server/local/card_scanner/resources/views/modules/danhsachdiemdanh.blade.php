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
						<form action="" method="get">
							<div class="row">
								<div class="col-lg-6">
									<div class="form-group">
										<label>Chọn môn</label>
										<select id="id_mon" class="form-control" name="id_mon">
											@foreach($monhoc as $val)
											<option value="{{ $val->id }}">{{ $val->ma_mon }}</option>
											@endforeach
										</select>
										<p class="text-danger">{{$errors->first('ma_mon')}}</p>
									</div>
								</div>
							</div>
							<div class="text-right">
								<button class="btn btn-primary"><i class="fe fe-eye view"></i> Xem</button>
								<button class="btn btn-success" name="export" type="submit"><i class="fe fe-arrow-down-circle view"></i> Xuất</button>
								{{-- ButtonImport --}}
								<button type="button" class="btn btn-primary" data-toggle="modal" data-target="#exampleModal">
										Import-SDcard
								</button>
								<!-- Modal -->
								<div class="modal fade" id="exampleModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
										<div class="modal-dialog" role="document">
										<div class="modal-content">
											<div class="modal-header">
											<h5 class="modal-title" id="exampleModalLabel">Nhập dữ liệu từ SD-card</h5>
											<button type="button" class="close" data-dismiss="modal" aria-label="Close">
												{{-- <span aria-hidden="true">&times;</span> --}}
											</button>
											</div>
											<div class="modal-body">
													<div class="col">
															<div class="">
																	@if(Session::has('MessageAPI'))
																	<div class="card-body">
																		<div name="MessSuccess" class="text-center alert alert-success mx-sm-3" role="alert">
																			{{Session::get('MessageAPI')}}
																		</div>
																	</div>
																	@else
																	<div class="card-body">
																		<div name="MessNull" class="text-center alert alert-warning mx-sm-3" role="alert">
																			Nhập File thông tin điểm danh SD/file.txt
																			{{Session::forget('MessageAPI')}}
																		</div>
																	</div>
																	@endif
															</div>
															<div class="">
																	<div class="card-body">
																		<form name="C123" action="{{ route('checkin') }}" class="form-inline" method="POST" enctype="multipart/form-data">
																			@csrf
																			<div class="form-group mx-sm-3">
																				<input type="file" class="form-control" name="filetxt">
																			</div>
																			{{-- <button name="checkinSV" type="submit" class="btn btn-info"><i class="fe fe-arrow-up-circle"></i> Nhập dữ liệu</button> --}}
																		</form>
																	</div>
															</div>
													</div>
											</div>
											<div class="modal-footer">
											<button type="button" class="btn btn-secondary" data-dismiss="modal">Close</button>
											<button name="C123" type="submit" class="btn btn-info"><i class="fe fe-arrow-up-circle"></i> Nhập</button>
											</div>
										</div>
										</div>
									</div>
							</div>
						</form>
					</div>
				</div>
			</div>
			
			<div class="col-lg-12">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title text-uppercase">Danh sách điểm danh</h3>
					</div>
					@if(count($data)>0)
					<div class="card-body">
						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>STT</th>
										<th>MSSV</th>
										<th>Tên sinh viên</th>
										<th>Mã môn</th>
										<th class="text-center">Số buổi có mặt</th>
										<!-- <th class="text-right">Chức năng</th> -->
									</tr>
								</thead>
								<tbody>
									@foreach($data as $key=> $val)
									<tr>
										<td>{{ $key+1 }}</td>
										<td>{{ $val->mssv }}</td>
										<td>{{ $val->ho . ' ' . $val->ten }}</td>
										<td>{{ $val->ma_mon }}</td>
										<td class="text-center">{{ $val->buoi_co_mat . '/' . $val->so_buoi }}</td>
										<!-- <td class="text-right">
											<a href="{{ url('quan-ly/chi-tiet-buoi-vang/'.$val->id_sinhvien.'/'.$val->mamon) }}" class="btn btn-success"><i class="fe fe-eye"></i> Xem chi tiết</a>
										</td> -->
									</tr>
									@endforeach

								</tbody>
							</table>
						</div>
					</div>
					@endif
				</div>
			</div>
		</div>
	</div>
</div>
<script>
	$('.view').click(function (e) { 
		console.log($('#lop').val())
		
	});
</script>
@endsection