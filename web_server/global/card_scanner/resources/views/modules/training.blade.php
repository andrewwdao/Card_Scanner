@extends('masterlayout')
@section('content')
<div id="content" class="page-main">
	<div class="container-fluid">
		<div class="row">
			<div class="col-lg-12">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title text-uppercase">Training cho sinh viên {{ $sinhvien->hoten }}</h3>
					</div>
					<div class="card-body">
						<div class="form-group">
							
							<form action="{{ route('traindata',[$mssv]) }}" enctype="multipart/form-data" method="post">
							{{ csrf_field() }}
								<div class="form-group">
							
									<div class="custom-file">
										<input id="train-data" type="file" class="custom-file-input" name="upload[]" multiple="multiple">
										
										<label class="custom-file-label" id="count">Nạp ảnh (Tối thiểu 3 ảnh)</label>
									</div>
								</div>

								<div class="form-group">
									<input class="btn btn-primary pull-right btn-lg " type="submit" name="submit" value="Upload ảnh">
								</div>
								<div class="form-group pt-3">
									@if(session()->has('result'))
									<p>Danh sách upload</p>
									<ul class="list-group">
									
										@if(count(session()->get('result')['done']) > 0)
										@foreach(session()->get('result')['done'] as $user)
										<li class="list-group-item list-group-item-success">{{ $user}}</li>
										@endforeach
										@endif
										@if(count(session()->get('result')['fail']) > 0)
										@foreach(session()->get('result')['fail'] as $user)
										<li class="list-group-item list-group-item-danger">{{ $user}}</li>
										@endforeach
										@endif
									
									</ul>
									@endif
								</div>
							</form>
						</div>
					
					</div>
				</div>
			</div>
			
		</div>
	</div>
</div>

<script>
$(document).ready(function () {
	$("#train-data").change(function(){
		$("#count").text('Đã nạp '+$("input:file")[0].files.length +' ảnh')
	});
});
</script>
@endsection