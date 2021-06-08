using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Diagnostics;

namespace BitmapFontConv
{
	class Bitmap
	{
		public struct BitmapFileHeader
		{
			public ushort Type { get; set; }
			public uint Size { get; set; }
			public ushort Reserved1 { get; set; }
			public ushort Reserved2 { get; set; }
			public uint OffBits { get; set; }
		}

		public struct BitmapInfoHeader
		{
			public uint Size { get; set; }
			public uint Width { get; set; }
			public uint Height { get; set; }
			public ushort Planes { get; set; }
			public ushort BitCount { get; set; }
			public uint Compression { get; set; }
			public uint SizeImage { get; set; }
			public uint XPiPerMeter { get; set; }
			public uint YPixPerMeter { get; set; }
			public uint ClrUsed { get; set; }
			public uint ClrImportant { get; set; }
		}

		public bool IsDataValid { get; private set; }
		public BitmapFileHeader FileHeader { get; set; }
		public BitmapInfoHeader InfoHeader { get; set; }
		public byte[] ImageData { get; private set; }
		

		public Bitmap(byte[] bmp_data)
		{
			var br = new BinaryReader(new MemoryStream(bmp_data));
			var fh = new BitmapFileHeader();
			var ih = new BitmapInfoHeader();

			fh.Type = br.ReadUInt16();
			fh.Size = br.ReadUInt32();
			fh.Reserved1 = br.ReadUInt16();
			fh.Reserved2 = br.ReadUInt16();
			fh.OffBits = br.ReadUInt32();

			ih.Size = br.ReadUInt32();
			ih.Width = br.ReadUInt32();
			ih.Height = br.ReadUInt32();
			ih.Planes = br.ReadUInt16();
			ih.BitCount = br.ReadUInt16();
			ih.Compression = br.ReadUInt32();
			ih.SizeImage = br.ReadUInt32();
			ih.XPiPerMeter = br.ReadUInt32();
			ih.YPixPerMeter = br.ReadUInt32();
			ih.ClrUsed = br.ReadUInt32();
			ih.ClrImportant = br.ReadUInt32();

			ImageData = br.ReadBytes(1 * 1024 * 1024);

			IsDataValid = CheckHeader(fh, ih, ImageData);
			if (IsDataValid) {
				FileHeader = fh;
				InfoHeader = ih;
			}

			br.Close();

			convRGB888toRGBA8888();
		}

		void convRGB888toRGBA8888()
		{
			/// �摜�f�[�^�̕��ёւ� ����� 24bit����32bit�ւ̕ϊ�(RGB888->RGBA8888)
			/// BMP�̉摜�f�[�^�͍������珇�Ԃɕ���ł���B�܂��A�e�s�̃f�[�^�T�C�Y��4byte���E�ɑ����邽�߂̃p�f�B���O�������Ă���\��������B
			/// �r�b�g�}�b�v�t�H���g�f�[�^�͍���̉�f����i�[���邽�߁A�����ŕ��ёւ������{����
			var ms = new MemoryStream(ImageData);
			var br = new BinaryReader(ms);
			byte[] rgba_data = new byte[InfoHeader.Width * 4 * InfoHeader.Height];
			int padding = 4 - (int)(InfoHeader.Width % 4);

			for (int row = 0; row < InfoHeader.Height; row++) {
				for (int pixel = 0; pixel < InfoHeader.Width; pixel++) {
					byte[] rgb = br.ReadBytes(3);
					byte[] rgba = new byte[4];

					// RGB -> RGBA
					if (!isTransparent(rgb)) {
						Array.ConstrainedCopy(rgb, 0, rgba, 1, rgb.Length);
						rgba[0] = 0xff;     // �����x
					}

					Array.ConstrainedCopy(rgba, 0, rgba_data, (int)(InfoHeader.Height - row - 1) * (int)(InfoHeader.Width * 4) + pixel * 4, rgba.Length);
				}

				// �p�f�B���O�ǂݔ�΂�
				br.ReadBytes(padding);
			}

			ImageData = rgba_data;
		}

		static bool isTransparent(byte[] rgb)
		{
			// ��(RGB:00ff00)�͓����F�Ƃ��Ĉ���
			return (rgb[0] == 0x00 && rgb[1] == 0xFF && rgb[2] == 0x00);
		}

		static bool CheckHeader(BitmapFileHeader fh, BitmapInfoHeader ih, byte[] data)
		{
			/// FileHeader
			// BM
			if (fh.Type != 0x4d42) return false;

			if (fh.Reserved1 != 0x0000) return false;
			if (fh.Reserved2 != 0x0000) return false;

			/// InfoHeader
			// Windows�`���̂ݑΉ�
			if (ih.Size != 40) return false;
			if (ih.Planes != 0x0001) return false;
			// 24Bit�̂ݑΉ�
			if (ih.BitCount != 24) return false;
			// �����k�̂ݑΉ�
			if (ih.Compression != 0x00) return false;
			// �T�C�Y�s��v
			if (ih.SizeImage != data.Length) return false;
			// �p���b�g��Ή�
			if (ih.ClrUsed != 0x00) return false;
			if (ih.ClrImportant != 0x00) return false;

			return true;
		}
	}
}
