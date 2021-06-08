using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace BitmapFontConv
{
	/// <summary>
	/// MainWindow.xaml �̑��ݍ�p���W�b�N
	/// </summary>
	public partial class MainWindow : Window
	{
		public MainWindow()
		{
			InitializeComponent();
		}

		private void button_Click(object sender, RoutedEventArgs e)
		{
			lbLog.Items.Clear();

			var cur = Environment.CurrentDirectory;

			// �Ώۂ�bmp����
			var bmps = Directory.EnumerateFiles(cur).Where(x => x.EndsWith(".bmp")).ToList();

			// �o�̓t�@�C������
			StreamWriter sw = new StreamWriter(cur + @"\" + textBox.Text);

			bool[] isExistChar = new bool[0x80];	// ASCII�R�[�h Max

			// ����f�B���N�g����[HEX].bmp����t�H���g�f�[�^�z��֕ϊ�
			foreach(string bmp_path in bmps) {
				var fname = bmp_path.Substring(bmp_path.LastIndexOf('\\') + 1);
				fname = fname.Remove(fname.LastIndexOf('.'));

				int ascii = int.Parse(fname, System.Globalization.NumberStyles.AllowHexSpecifier);
				FileStream fs = new FileStream(bmp_path, FileMode.Open);
				BinaryReader br = new BinaryReader(fs);
				
				var bmp_data = br.ReadBytes(1*1024*1024);

				br.Close();

				// BMP�f�[�^����Bitmap�N���X����
				Bitmap bmp = new Bitmap(bmp_data);
				if (!bmp.IsDataValid) continue;

				// �t�H���g�f�[�^�i�P�����j�̏o��
				if( writeBmpFontData(fname, bmp, sw)) {
					isExistChar[ascii] = true;
				}
			}

			// �t�H���g�f�[�^�̃|�C���^�z��o��
			writeBmpFontDataArray(isExistChar, sw);

			sw.Close();

			lbLog.Items.Add("Finish.");
		}

		private bool writeBmpFontData(string fname, Bitmap bmp, StreamWriter output)
		{
			// Width(4byte), Height(4byte), BitCount(4byte), DataSize(4byte), Data(Dynamic)�̏��ɏo��
			output.WriteLine("const unsigned char bmp_fontdata_" + fname + "[] = {");
			output.WriteLine("\t" + bin2str(BitConverter.GetBytes(bmp.InfoHeader.Width)) + ", // Width");
			output.WriteLine("\t" + bin2str(BitConverter.GetBytes(bmp.InfoHeader.Height)) + ", // Height");
			//sw.WriteLine("\t" + bin2str(BitConverter.GetBytes(bmp.InfoHeader.BitCount)) + ", // BitCount");
			output.WriteLine("\t" + bin2str(BitConverter.GetBytes(bmp.ImageData.Length)) + ", // DataSize");

			var br = new BinaryReader(new MemoryStream(bmp.ImageData));
			for (int i = 0; i < bmp.InfoHeader.Height; i++) {
				byte[] row = br.ReadBytes((int)(bmp.InfoHeader.Width * 4));
				output.WriteLine("\t" + bin2str(row) + (i == bmp.InfoHeader.Height - 1 ? "" : ","));
			}
			output.WriteLine("};");
			output.WriteLine("");

			lbLog.Items.Add(fname + ".bmp, W:" + bmp.InfoHeader.Width + ", H:" + bmp.InfoHeader.Height + ", BC:" + bmp.InfoHeader.BitCount + ", ImageLength:" + bmp.ImageData.Length);

			return true;
		}

		private bool writeBmpFontDataArray(bool[] existFont, StreamWriter output)
		{
			output.WriteLine("const unsigned char* bmp_fontdata[] = {");
			for (int i = 0; i < existFont.Length; i++) {

				string line = "\t";
				if (existFont[i]) {
					line += "bmp_fontdata_0" + i.ToString("X") + ", // '" + Encoding.ASCII.GetString(new byte[] { (byte)i }) + "'";
				}
				else {
					line += "0x00,";
				}

				output.WriteLine(line);
			}
			output.WriteLine("\t0x00 // End");
			output.WriteLine("};");

			return true;
		}

		private string bin2str(byte[] data)
		{
			return "0x" + BitConverter.ToString(data).Replace("-", ", 0x");
		}
	}
}
