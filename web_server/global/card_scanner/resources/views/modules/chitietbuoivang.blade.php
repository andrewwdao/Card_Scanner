@extends('masterlayout')
@section('content')
<div id="content" class="page-main">
	<div class="container-fluid">
		<div class="row">
			<div class="col-lg-12">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title text-uppercase">Danh sách điểm danh</h3>
					</div>
					<div class="card-body">
						<div class="table-responsive">
							<table class="table table-hover">
								<thead>
									<tr>
										<th>STT</th>
										<th>MSSV</th>
										<th>Tên sinh viên</th>
										<th>Class</th>
										<th class="text-center">Có mặt ngày</th>
										<th class="text-right">Chức năng</th>
									</tr>
								</thead>
								<tbody>
									@foreach($data as $key=>$val)
									<tr>
										<td hidden class='mamon'>{{ $val->mamon }}</td>
										<td>{{ $key+1 }}</td>
										<td class='masv'>{{ $val->masv }}</td>
										<td>{{ $val->hoten }}</td>
										<td>{{ $val->mamon }}</td>
										<td class="text-center buoivang">{{ Carbon\Carbon::parse($val->buoivang)->format('d-m-Y') }}</td>
										<td class="text-right">
											<a class="btn btn-danger delete" style="color:#fff"><i class="fe fe-trash"></i> Xóa</a>
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
		var mamon=$(this).closest('tr').find('.mamon').text()
		var masv=$(this).closest('tr').find('.masv').text()
		var buoivang=$(this).closest('tr').find('.buoivang').text()
		console.log(buoivang)
		$.ajax({
			type: "post",
			url: "{{ route('Destroy_diemdanh') }}",
			data: {
				"_token":"{{ csrf_token() }}",
				'mamon':mamon,
				'masv':masv,
				'buoivang':buoivang
			},
			success: function (response) {
				if(response=='ok')
					location.reload()
			
			}
		});
		
	});
</script>
@endsection