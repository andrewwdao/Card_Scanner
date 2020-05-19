<div class="header py-2">
  <div class="container-fluid">
    <div class="d-flex">
      <button type="button" id="sidebarCollapse" class="btn btn-primary btn-sidebar mr-1">
        <i class="fa fa-bars"></i>
    </button>      
    <div class="d-flex order-lg-2 ml-auto">
        <!-- User -->
        <div class="dropdown">
          <a href="#" class="nav-link pr-0 leading-none" data-toggle="dropdown">
            <span class="avatar" style="background-image: url({!!asset('assets/images/boss.png') !!})"></span>
            <span class="ml-2 d-none d-lg-block">
              <span class="text-default">{{Auth::guard('admin')->user()->taikhoan}}</span>
              <small class="text-muted d-block mt-1">Administrator</small>
            </span>
          </a>
          <div class="dropdown-menu dropdown-menu-right dropdown-menu-arrow">
            <a class="dropdown-item" href="#">
              <i class="fe fe-user" style="color:#999;"></i> Profile
            </a>
            <div class="dropdown-divider"></div>
          <a class="dropdown-item" href="{{route('logout')}}">
              <i class="fe fe-log-out" style="color:#999;"></i> Đăng xuất
            </a>
          </div>
        </div>
        <!-- end: User -->
      </div>
    </div>
  </div>
</div>