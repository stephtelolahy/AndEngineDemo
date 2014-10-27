package com.sampleandengine;

import org.andengine.engine.camera.Camera;
import org.andengine.engine.options.EngineOptions;
import org.andengine.engine.options.ScreenOrientation;
import org.andengine.engine.options.resolutionpolicy.IResolutionPolicy;
import org.andengine.engine.options.resolutionpolicy.RatioResolutionPolicy;
import org.andengine.entity.scene.Scene;
import org.andengine.entity.sprite.Sprite;
import org.andengine.opengl.texture.ITexture;
import org.andengine.opengl.texture.bitmap.AssetBitmapTexture;
import org.andengine.opengl.texture.region.ITextureRegion;
import org.andengine.opengl.texture.region.TextureRegionFactory;
import org.andengine.ui.activity.SimpleBaseGameActivity;

import java.io.IOException;


public class StartupActivity extends SimpleBaseGameActivity {

    private static final int CAMERA_WIDTH = 800;
    private static final int CAMERA_HEIGHT = 480;

    private Camera mCamera;

    private ITextureRegion mTextureRegion;
    private ITexture mTexture;

    @Override
    public EngineOptions onCreateEngineOptions() {
        mCamera = new Camera(0, 0, CAMERA_WIDTH, CAMERA_HEIGHT);
        IResolutionPolicy resolutionPolicy =
                new RatioResolutionPolicy(CAMERA_WIDTH, CAMERA_HEIGHT);

        return new EngineOptions(true,
                ScreenOrientation.LANDSCAPE_FIXED,
                resolutionPolicy,
                mCamera);
    }

    @Override
    protected void onCreateResources() {

        try {

            mTexture = new AssetBitmapTexture(getTextureManager(), getAssets(), "player.png");
            mTextureRegion = TextureRegionFactory.extractFromTexture(mTexture);
            mTexture.load();

        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    @Override
    protected Scene onCreateScene() {

//        Scene scene = new Scene();
//        scene.getBackground().setColor(0.2f, 0.5f, 0.7f);

        Scene scene = new Scene();
        scene.getBackground().setColor(0.2f, 0.5f, 0.7f);
        Sprite sprite = new Sprite(mCamera.getWidth() / 2, mCamera.getHeight() / 2,
                mTextureRegion, getVertexBufferObjectManager());
        scene.attachChild(sprite);

        return scene;
    }
}
