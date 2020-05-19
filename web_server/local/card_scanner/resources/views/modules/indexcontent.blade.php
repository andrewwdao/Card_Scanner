@extends('masterlayout')
@section('content')
<div id="content" class="page-main">
	<div class="container-fluid">
		<div class="row">
			<div class="col-lg-8">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title">Nạp hình ảnh</h3>
					</div>
					<div class="card-body">
						<div class="dimmer">
							<div class="loader"></div>
							<div class="dimmer-content">
								<div class="img-detection">
									<img class="rounded" width="100%" src="{!!asset('assets/images/cc.png') !!}" alt="">
									<!-- <span class="detected">Name</span>
									<span class="undetected">Name</span> -->
								</div>
							</div>
						</div>
						
					</div>
				</div>
			</div>
			<div class="col-lg-4">
				<div class="card">
					<div class="card-status bg-blue"></div>
					<div class="card-header">
						<h3 class="card-title">Thao tác</h3>
					</div>
					<div class="card-body">
						
							<div class="form-group">
								<label>Chọn Môn</label>
								<select  id="monhoc" class="form-control">
								@forelse($dsmon as $mon)
								<option value="{{ $mon->mamon }}" selected>{{ $mon->tenmon }}</option>
								@empty
								<option value="">Chưa có môn </option>
								@endforelse
									
								</select>
							</div>
							<form id="data" method="post" enctype="multipart/form-data">
							<div class="form-group">
								<div class="custom-file">
									<input type="file" class="custom-file-input" onchange="read(this)" name="fileanh">
									<label class="custom-file-label">Chọn ảnh</label>
								</div>
							</div>
							<div class="text-right">
								<button class="btn btn-primary" type="submit"><i class="fe fe-check"></i> Điểm Danh</button>
							</div>
						</form>
					</div>
				</div>
			</div>
		</div>
	</div>
</div>
<script>
function remove(){
	$('.detected').remove();
	$('.undetected').remove();
}
function read(input){
	remove()
	if (input.files && input.files[0]) {
                var reader = new FileReader();

                reader.onload = function (e) {
                    $('.rounded')
                        .attr('src', e.target.result);
                };

                reader.readAsDataURL(input.files[0]);
            }


}


function detect_face()
{
	var image = new Image();
	image.src = $('.rounded').attr("src");
	var nwidth = image.naturalWidth;
	var nheight = image.naturalHeight;
	var width = Math.round($('.rounded').width());
	var height = Math.round($('.rounded').height());
	console.log(width + ':' + height +'-' +nwidth +":" +nheight);

	return {"nwdith":nwidth,'nheight':nheight,"width":width,"height":height};

}
$(document).ready(function () {
	// $("#anhup").change(function(){
	// 	$(".rounded").attr('src',formData.get('fileanh'))
	// })
	
	$("#data").submit(function(e) {
	remove()
	
    e.preventDefault();  
	// console.log($("#lophoc").val());  
    var formData = new FormData(this);
	var reader = new FileReader();
          reader.onload = function (e) {
              $('#img-detection').html('<img src="'+formData.get('fileanh')+'">');
          }
          reader.readAsDataURL(formData.get('fileanh'));
	var toado = detect_face();
	formData.append('monhoc',$("#monhoc").val());
	formData.append('_token',"{{csrf_token()}}");
    $.ajax({
        url: '{{ route('diemdanh') }}',
        type: 'POST',
        data: formData,
        beforeSend: function(){
     		$(".dimmer").addClass('active');
   		},
        success: function (data) {
        	$(".dimmer").removeClass('active');
            console.log(data);
			if(data.hasOwnProperty('Error'))
			{
				alert(data.Error);
			}
			$.each(data['images'],function(index,val1){
				
					if('transaction' in val1){
						var left = Math.round(val1['transaction'].topLeftX * toado.width / toado.nwdith);
						var top = Math.round((val1['transaction'].topLeftY * toado.height) / toado.nheight);
						var width = val1['transaction'].width * toado.width / toado.nwdith;
						var height = val1['transaction'].height * toado.height / toado.nheight;
						console.log(val1['transaction'].topLeftX)
						console.log(left + '::' + top + '::'+width+'::'+height)

						if(val1['transaction'].status === 'success')
						{
							$('<div>', {
          'class':'detected',
          'css': {
            'position': 'absolute',
            'left':   left + 'px',
            'top':    top + 'px',
            'width':  width + 'px',
            'height': height + 'px'
          }
        }).insertAfter($('.rounded'))
						}
						else{
							$('<div>', {
          'class':'undetected',
          'css': {
            'position': 'absolute',
            'left':   left + 'px',
            'top':    top + 'px',
            'width':  width + 'px',
            'height': height + 'px'
          }
        }).insertAfter($('.rounded'))
						}
						
					}
				
			})
        },
        cache: false,
        contentType: false,
        processData: false
    });
});
});
</script>
@endsection