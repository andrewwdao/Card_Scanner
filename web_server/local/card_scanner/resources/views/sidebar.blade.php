
<nav id="sidebar">
    <div class="profile">
        <div class="d-flex justify-content-center py-4">
                <span class="avatar avatar-xxl" style="background-image: url({!!asset('assets/images/boss.png') !!}"></span>
        </div>
        <h5 class="text-center">Admin</h5>
    </div>
    <ul class="list-unstyled components">
       <!--  <li @if(Request::segment(2)=="trang-chu") class="active" @endif>
            <a href="{{route('trang-chu')}}"><i class="fe fe-user"></i> Điểm danh</a>
        </li>
        <li @if(Request::segment(2)=="training-list" || Request::segment(2)=="training") class="active" @endif>
            <a href="{{route('training-list')}}"><i class="fe fe-gitlab"></i> Training khuôn mặt</a>
        </li>
         <li @if(Request::segment(2)=="quan-ly-khuon-mat" || Request::segment(2)=="quan-ly-khuon-mat") class="active" @endif>
            <a href="{{route('qlkhuonmat')}}"><i class="fe fe-github"></i> Quản lý khuôn mặt</a>
        </li> -->
        <li>
            <a href="#quanly" data-toggle="collapse" aria-expanded="false"><i class="fe fe-folder"></i> Quản lý<i class="dropdown-toggle float-right"></i></a>
            <ul id="quanly" class="collapse list-unstyled">
                <li @if(Request::segment(2)=='quan-ly-mon-hoc') class="active" @endif><a href="{{route('gquan-ly-mon-hoc')}}">Danh sách môn học</a></li>
                <li @if (Request::segment(2)=='quan-ly-sinh-vien') class="active" @endif><a href="{{route('quan-ly-sinh-vien')}}">Danh sách sinh viên</a></li>
                <li @if (Request::segment(2)=='quan-ly-lop') class="active" @endif><a href="{{route('gquan-ly-lop')}}">Danh sách lớp</a></li>
            </ul>
        </li>
         <li >
            <a href="{{route('quan-ly-diem-danh')}}"><i class="fe fe-github"></i>Danh sách điểm danh</a>
        </li>
       
    </ul>
     
</nav>