
=Requirements=

You will need a patched Android NDK which includes _gcc 4.6_ support. [Crystax](http://www.crystax.net/en/android/ndk) is the recommended NDK to use.
Also you need the SDL sourcecode, placed in ```jni/SDL```

=Building=

For building an Android version you need to specify the ```sdk.dir``` and ```ndk.dir``` in the file local.properties.

Example local.properties:
```
sdk.dir=/home/user/android-sdk
ndk.dir=/home/user/android-ndk

```
