using System.Reflection;
using System.Resources;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Windows;

// �A�Z���u���Ɋւ����ʏ��͈ȉ��̑����Z�b�g���Ƃ����Đ��䂳��܂��B
// �A�Z���u���Ɋ֘A�t�����Ă������ύX����ɂ́A
// �����̑����l��ύX���Ă��������B
[assembly: AssemblyTitle("BitmapFontConv")]
[assembly: AssemblyDescription("")]
[assembly: AssemblyConfiguration("")]
[assembly: AssemblyCompany("AVCMMS")]
[assembly: AssemblyProduct("BitmapFontConv")]
[assembly: AssemblyCopyright("Copyright  AVCMMS 2018")]
[assembly: AssemblyTrademark("")]
[assembly: AssemblyCulture("")]

// ComVisible �� false �ɐݒ肷��ƁA���̌^�͂��̃A�Z���u������ COM �R���|�[�l���g����
// �Q�ƕs�\�ɂȂ�܂��BCOM ���炱�̃A�Z���u�����̌^�ɃA�N�Z�X����ꍇ�́A
// ���̌^�� ComVisible ������ true �ɐݒ肵�Ă��������B
[assembly: ComVisible(false)]

//���[�J���C�Y�\�ȃA�v���P�[�V�����̃r���h���J�n����ɂ́A
//.csproj �t�@�C���� <UICulture>CultureYouAreCodingWith</UICulture> ��
//<PropertyGroup> �����Őݒ肵�܂��B���Ƃ��΁A
//�\�[�X �t�@�C���ŉp����g�p���Ă���ꍇ�A<UICulture> �� en-US �ɐݒ肵�܂��B���ɁA
//���� NeutralResourceLanguage �����̃R�����g���������܂��B���̍s�� "en-US" ��
//�v���W�F�N�g �t�@�C���� UICulture �ݒ�ƈ�v����悤�X�V���܂��B

//[assembly: NeutralResourcesLanguage("en-US", UltimateResourceFallbackLocation.Satellite)]


[assembly: ThemeInfo(
	ResourceDictionaryLocation.None, //�e�[�}�ŗL�̃��\�[�X �f�B�N�V���i�����u����Ă���ꏊ
									 //(���\�[�X���y�[�W�A
									 //�܂��̓A�v���P�[�V���� ���\�[�X �f�B�N�V���i���Ɍ�����Ȃ��ꍇ�Ɏg�p����܂�)
	ResourceDictionaryLocation.SourceAssembly //�ėp���\�[�X �f�B�N�V���i�����u����Ă���ꏊ
											  //(���\�[�X���y�[�W�A
											  //�A�v���P�[�V�����A�܂��͂�����̃e�[�}�ŗL�̃��\�[�X �f�B�N�V���i���ɂ�������Ȃ��ꍇ�Ɏg�p����܂�)
)]


// �A�Z���u���̃o�[�W�������͎��� 4 �̒l�ō\������Ă��܂�:
//
//      ���W���[ �o�[�W����
//      �}�C�i�[ �o�[�W����
//      �r���h�ԍ�
//      Revision
//
// ���ׂĂ̒l���w�肷�邩�A���̂悤�� '*' ���g���ăr���h����у��r�W�����ԍ��� 
// ����l�ɂ��邱�Ƃ��ł��܂�:
// [assembly: AssemblyVersion("1.0.*")]
[assembly: AssemblyVersion("0.1.0.0")]
[assembly: AssemblyFileVersion("0.1.0.0")]
