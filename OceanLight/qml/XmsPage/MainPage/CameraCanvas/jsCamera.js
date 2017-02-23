Qt.include("../../../Controls/three.js")

var camera, scene, renderer, dirLight, hemiLight;
var mixers = [];
var stats;
var clock = new THREE.Clock();


function addSceneLight(){
    hemiLight = new THREE.HemisphereLight( 0xffffff, 0xffffff, 0.6 );
    hemiLight.color.setHSL( 0.6, 1, 0.6 );
    hemiLight.groundColor.setHSL( 0.095, 1, 0.75 );
    hemiLight.position.set( 0, 500, 0 );

    scene.add( hemiLight );

    dirLight = new THREE.DirectionalLight( 0xffffff, 1 );
    dirLight.color.setHSL( 0.1, 1, 0.95 );
    dirLight.position.set( -1, 1.75, 1 );
    dirLight.position.multiplyScalar( 50 );
    scene.add( dirLight );

    dirLight.castShadow = true;
    dirLight.shadow.mapSize.width = 2048;
    dirLight.shadow.mapSize.height = 2048;

    var d = 50;
    dirLight.shadow.camera.left = -d;
    dirLight.shadow.camera.right = d;
    dirLight.shadow.camera.top = d;
    dirLight.shadow.camera.bottom = -d;
    dirLight.shadow.camera.far = 3500;
    dirLight.shadow.bias = -0.0001;

}



function initializeGL(canvas) {

    camera = new THREE.PerspectiveCamera(30, canvas.width / canvas.height,1, 5000);
    camera.position.z = 250;



    scene = new THREE.Scene();
    addSceneLight();



    var loader = new THREE.JSONLoader();
    loader.load( 'flamingo.js', function( geometry ) {
                var material = new THREE.MeshPhongMaterial(
                    {
                        color: 0xffffff,
                        specular: 0xffffff,
                        shininess: 20,
                        morphTargets: true,
                        vertexColors: THREE.FaceColors,
                        shading: THREE.FlatShading }
                    );
                var mesh = new THREE.Mesh( geometry, material );
                var s = 0.35;
                mesh.scale.set( s, s, s );
                mesh.position.y = 15;
                mesh.rotation.y = -1;
                mesh.castShadow = true;
                mesh.receiveShadow = true;

                scene.add( mesh );
                var mixer = new THREE.AnimationMixer( mesh );
                mixer.clipAction( geometry.animations[ 0 ] ).setDuration( 1 ).play();
                mixers.push( mixer );
            } );

    //背景透明
    renderer = new THREE.Canvas3DRenderer({ canvas: canvas, antialias: true, alpha:true,devicePixelRatio: canvas.devicePixelRatio });
    renderer.setClearColor(0xFFFFFF, 0.0);
    //renderer.setClearColor( scene.fog.color );
    //renderer.setClearAlpha(0);
    renderer.setSize(canvas.width, canvas.height);

    renderer.gammaInput = true;
    renderer.gammaOutput = true;
    renderer.shadowMap.enabled = true;
    renderer.shadowMap.renderReverseSided = false;
}

function resizeGL(canvas) {
    camera.aspect = canvas.width / canvas.height;
    camera.updateProjectionMatrix();

    renderer.setPixelRatio(canvas.devicePixelRatio);
    renderer.setSize(canvas.width, canvas.height);
}

function render() {
    var delta = clock.getDelta();
    for ( var i = 0; i < mixers.length; i ++ ) {
        mixers[ i ].update( delta );
    }
    renderer.render( scene, camera );
}

function paintGL(canvas) {
    render();
}


