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
										<input type="text" class="form-control" disabled value="{{ $data->malop }}" name="malop">
										<p class="text-danger">{{$errors->first('malop')}}</p>
									</div>
								</div>
								<div class="col-lg-6">
										<div class="form-group">
											<label>Tên lớp</label>
											<input type="text" class="form-control" value="{{ $data->tenlop }}" name="tenlop">
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
		</div>
	</div>
</div>

@endsection