@extends('masterlayout')
@section('content')
<div id="content" class="page-main">
	<div class="container-fluid">
		<div class="row">
			<div class="col-lg-12">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title text-uppercase">Chọn lớp</h3>
					</div>
					<div class="card-body">
						<form action="">
							<div class="form-group">
								<select  id="dslop" class="form-control">
								@if($dslop)
									@forelse($dslop as $lop)
									<option value="{{ $lop->malop }}">{{ $lop->tenlop }} </option>
									@empty
									<option value="">Không có dữ liệu </option>
									@endforelse
									@endif
								
									<!-- <option value="">Optio illo asperiores dignissimos! Laudantium.</option>
									<option value="">At veritatis sunt officiis, nesciunt.</option> -->
								</select>
							</div>
							<div class="text-right">
								<button class="btn btn-primary btn-nap"><i class="fe fe-arrow-down-circle"></i> Nạp danh sách lớp</button>
							</div>
						</form>
					</div>
				</div>
			</div>
			<div class="col-lg-12">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title text-uppercase">Danh sách sinh viên <span id="tenlop"></span> </h3>
					</div>
					<div class="card-body">
						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>STT</th>
										<th>Họ tên</th>
										<th class="text-right">Chức năng</th>
									</tr>
								</thead>
								<tbody id="body-list">
									

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

	$('.btn-nap').click(function(e){
		e.preventDefault();
		var dslop = $('#dslop').val();
		$.ajax({
			type: "get",
			url: "{{ route('ds_sinhvien_lop') }}",
			data: {"malop" : dslop},
			success: function (response) {
				$("#body-list").html(response['ds']);
				$("#tenlop").html(response['tenlop']);
				console.log(response['tenlop']);
			}
		});
	})

</script>
@endsection