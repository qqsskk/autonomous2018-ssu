autonomous2018-ssu
==================
숭실대학교 기계공학과, 스마트시스템소프트웨어학과 깃 저장소 입니다.
-------------------------------------------------------------------
저장소 관리자 : 스마트16박태욱()
본 저장소는 관리자가 허가한 사람만 접근할 수 있습니다.
---------------------------------------------------------------
현재 branch는 'vision_seul' 입니다

vision 디렉토리를 작성하는 브랜치입니다

[ 패키지 ]
camera_image : 웹캠 영상을 받아오는 패키지
lane_detection : 차선 검출을 수행하는 패키지
cal_distance : 실제 거리를 계산하는 패키지
convert_cloud : 차선을 point_cloud2 타입 메세지로 변환해주는 패키지
pointcloud_to_laserscan : 포인트클라우드를 레이저 스캔으로 변경해주는 패키지

[ 런치 ]
vision_launch.launch : 비전 센싱에 관련된 패키지를 자동적을 쇨행시켜주는 런치파일
현재 차선을 point_cloud2로 변환하는 것까지 수행

[ Rviz 설정파일 ]
vision.rviz : 인식된 차선의 point_cloud2 데이터를 Rviz상에서 관찰하기 위한 Rviz 설정파일

---------------------------------------------------------------

1. 저장소 사용법
 1. 작업 디렉토리를 최신 로컬상태로 변경

    git checkout master
 2. 커밋 히스토리 확인

    git log --graph --decorate --oneline --all -n

 n 대신 확인하고 싶은 커밋의 개수를 넣습니다. 디폴트는 모든 커밋
 3. 작업 디렉토리를 원격저장소로부터 업데이트

    git checkout master
    git push upstream master

# 깃 관리자 외 주의할점
1. 작업 디렉토리는 읽기 전용으로만 쓰세요! 파일의 내용을 바꾸거나 삭제, 또는 추가하면 안됩니다.
2. 위 명령어 외 다른 명령어 사용금지(ex add, commit, reset, 특히 push)
3. 문제 발생시 `카톡이나 슬랙에 문의해주세요.
