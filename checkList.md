# minirt 과제 목록!!!!!

- [x] 창(Window) 관리는 매끄럽게 유지되어야합니다 : 다른 창으로 변경, 최소화 등등.
- [x] 최소한 5가지 단순한 기하학적 개체를 구현해야 합니다: **평면(plane)**, **구(sphere)**, **원통(cylinder)**, **정사각형(square)**, **삼각형(triangle)**
- [x] 해당되는 경우 가능한 모든 교차점(intersection)과 개체 내부(inside of the object)를 올바르게 처리해야합니다.
- [x] 프로그램은 개체의 고유 한 크기 속성을 조정할 수 있어야합니다(resize): 구의 반지름, 정사각형의 변의 길이, 원통의 너비와 높이.
- [x] 프로그램은 이동 및 회전 변환을 객체(Object), 조명(Light), 카메라(Camera)에 적용 할 수 있어야합니다. (회전 불가능한 구체(Sphere), 삼각형(triangle) 및 조명은 제외)
- [x] 조명 관리 : Spot brightness(광원?), Hard shadows(강한 그림자), Ambience lighting(주변광, 조도 - 객체는 절대 완전한 어둠속에 있을 수 없다). 빛에 색 적용이나, 다중 광원 적용은 정확하게 다루어져야 한다.
- [x] Deepthought 이 언젠가 눈이 생겨 당신의 프로젝트를 평가할 수 있게 될 때를 대비하거나, 아름다운 랜더링 결과물을 당신의 데스크탑 배경화면으로 만들 수 있게 하기 위해, 당신의 프로그램은 두번째 인자가 --save 일 때 반드시 랜더링된 이미지를 bmp 파일로 저장할 수 있어야 합니다.
- [x] 두 번째 인자가 제공되지 않으면 프로그램은 창에 이미지를 표시하고 다음 규칙을 따라야합니다.

>- [x] ESC를 누르면 창을 닫고 프로그램을 깨끗하게 종료해야합니다.
>- [x] 창의 프레임에있는 빨간색 십자가(종료 버튼)을 클릭하면 창을 닫고 프로그램을 깨끗하게 종료해야합니다.
>- [x] 선언 된 창 크기가 디스플레이 해상도보다 크면 창 크기는 현재 디스플레이 해상도에 따라 설정됩니다.
>- [x] 카메라가 두 개 이상인 경우 당신이 설장한 키보드 입력(key pressing)을 통해 카메라간에 전환 할 수 있어야합니다.
>- [x] minilibX의 이미지 사용을 적극 권장합니다.(image관련 함수 사용 권장하는 듯)

- [x] 프로그램은 `.rt` 확장자인 '장면 설명 파일'을 첫 번째 인수로 받아야합니다.

>- [x] 파일은 창 과 렌더링 된 이미지 크기를 포함됩니다. 이 말은 당신의 miniRT가 가능한 모든 크기로 랜더링이 가능해야 한다는 뜻입니다.
>- [x] 각 요소는 하나 이상의 줄 바꿈으로 구분되어 있습니다.
>- [x] 요소의 각 정보는 하나 이상의 공백으로 구분되어 있습니다.
>- [x] 파일에서 요소들은 임의의 순서로 정렬되어 있습니다.
>- [x] 대문자로 정의 된 요소는 '장면 설명 파일'에서 한 번만 선언될 수 있습니다.
>- [x] 각 요소의 첫 번째 정보는 유형 식별자(Specifier) (하나 또는 두 개의 문자로 구성됨)이며 반드시 다음과 같은 순서로 각 요소에 대한 특정 정보가 이어집니다 :
- [x] 파일에서 어떤 종류의 잘못된 구성이 발견되면 프로그램이 제대로 종료되고 "Error\ n"을 반환 한 다음 사용자가 선택한 명시적 오류 메시지를 반환해야합니다.
- [x] 방어를 위해, 생성 할 요소의 제어를 용이하게하기 위해 기능적인 것에 초점을 맞춘 전체 장면 세트를 갖는 것이 이상적 일 것입니다. (뭔소리인지 잘 모르겠음 parsing을 잘 해서 관리하라는 건가?)
>  * For the defence, it would be ideal for you to have a whole set of scenes with the
focus on what is functional, to facilitate the control of the elements to create. _ 원문

### 🥊 Bonus part

분명히 Ray Tracing 기술은 반사, 투명도, 굴절, 더 복잡한 오브젝트, 부드러운 그림자, 화선, 전역 조명, 범프 매핑, .obj 파일 렌더링 등과 같은 더 많은 것을 처리 할 수 ​​있습니다. 그러나 miniRT 프로젝트의 경우에는 첫 번째 레이트 레이서와 CGI의 첫 번째 단계는 간단합니다. 따라서 여기에 구현할 수있는 몇 가지 간단한 보너스 목록이 있습니다. 더 큰 보너스를 원할 경우이 작은 작업이 완료되고 완전히 작동 한 후 나중에 개발자 생활에서 새 광선 추적기를 다시 코딩하는 것이 좋습니다.

##### Bonus list:
>- [x] Normal disruption e.g. using sine which gives a wave effect.
>- [x] Color disruption: checkerboard.
>- [x] Color disruption: rainbow effect using object’s normal.
>- [x] Parallel light following a precise direction.
>- [x] Compound element: Cube (6 squares).
>- [x] Compound element: Pyramid (4 triangles, 1 square).
>- [x] Putting caps on size-limited cylinders.
>- [ ] One other 2nd degree object: Cone, Hyperboloid, Paraboloid..
>- [ ] One color filter: Sepia, R/G/B filters..
>- [x] Anti-aliasing.
>- [ ] Simple stereoscopy (like red/green glasses).
>- [x] Multithreaded rendering.
>- [x] Sphere texturing: uv mapping.
>- [ ] Handle bump map textures.
>- [x] A beautiful skybox.
>- [x] Keyboard interactivity (translation/rotation) with camera.
>- [x] Keyboard interactivity (translation/rotation) with objects.
>- [x] Changing the camera rotation with the mouse.