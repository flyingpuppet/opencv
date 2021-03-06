inherited Form_DataPath: TForm_DataPath
  Left = 234
  Top = 173
  Width = 795
  Height = 478
  Caption = 'Data Path'
  OldCreateOrder = True
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 787
    Height = 441
    Align = alTop
    BevelOuter = bvNone
    TabOrder = 0
    object GroupBox3: TGroupBox
      Left = 2
      Top = 104
      Width = 223
      Height = 71
      Caption = 'Format'
      TabOrder = 0
      object rb_PC: TRadioButton
        Left = 24
        Top = 24
        Width = 65
        Height = 17
        Caption = 'PC'
        TabOrder = 0
        OnClick = rb_PCClick
      end
      object rb_VD: TRadioButton
        Tag = 1
        Left = 104
        Top = 24
        Width = 58
        Height = 17
        Caption = 'VD'
        Checked = True
        TabOrder = 1
        TabStop = True
        OnClick = rb_PCClick
      end
    end
    object Button11: TButton
      Left = 114
      Top = 16
      Width = 75
      Height = 25
      Caption = 'pixle swap'
      TabOrder = 1
    end
    object CB_Half: TCheckBox
      Left = 10
      Top = 19
      Width = 89
      Height = 17
      Caption = 'Half Display'
      TabOrder = 2
    end
    object Button1: TButton
      Left = 192
      Top = 16
      Width = 75
      Height = 25
      Caption = 'Refresh'
      TabOrder = 3
      OnClick = Button1Click
    end
    object GB_InputFormat: TGroupBox
      Left = 2
      Top = 174
      Width = 249
      Height = 57
      Caption = 'Input Format'
      TabOrder = 4
      object rb_In_2D: TRadioButton
        Left = 8
        Top = 24
        Width = 41
        Height = 17
        Caption = '2D'
        TabOrder = 0
        OnClick = rb_In_2DClick
      end
      object rb_In_3DTB: TRadioButton
        Tag = 2
        Left = 120
        Top = 24
        Width = 57
        Height = 17
        Caption = '3D TB'
        Checked = True
        TabOrder = 1
        TabStop = True
        OnClick = rb_In_2DClick
      end
      object rb_In_3DLR: TRadioButton
        Tag = 1
        Left = 56
        Top = 24
        Width = 57
        Height = 17
        Caption = '3D L/R'
        TabOrder = 2
        OnClick = rb_In_2DClick
      end
      object rb_In_3DSBS: TRadioButton
        Tag = 3
        Left = 176
        Top = 24
        Width = 65
        Height = 17
        Caption = '3D SBS'
        TabOrder = 3
        OnClick = rb_In_2DClick
      end
    end
    object GroupBox1: TGroupBox
      Left = 256
      Top = 174
      Width = 241
      Height = 57
      Caption = 'Output Format'
      TabOrder = 5
      object rb_Out_2D: TRadioButton
        Left = 8
        Top = 24
        Width = 65
        Height = 17
        Caption = '2D'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = rb_Out_3DActiveClick
      end
      object rb_Out_3DPassive: TRadioButton
        Tag = 1
        Left = 64
        Top = 24
        Width = 89
        Height = 17
        Caption = '3D Passive'
        TabOrder = 1
        OnClick = rb_Out_3DActiveClick
      end
      object rb_Out_3DActive: TRadioButton
        Tag = 2
        Left = 152
        Top = 16
        Width = 65
        Height = 17
        Caption = '3D Active'
        TabOrder = 2
        OnClick = rb_Out_3DActiveClick
      end
      object CB_Samsung: TCheckBox
        Left = 153
        Top = 32
        Width = 78
        Height = 17
        Caption = 'Samsung'
        Enabled = False
        TabOrder = 3
        OnClick = CB_SamsungClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 2
      Top = 232
      Width = 167
      Height = 201
      Caption = 'Input VSync'
      TabOrder = 6
      object rb_In_50: TRadioButton
        Left = 8
        Top = 16
        Width = 65
        Height = 17
        Caption = '50Hz'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = rb_In_50Click
      end
      object rb_In_60: TRadioButton
        Tag = 1
        Left = 8
        Top = 32
        Width = 65
        Height = 17
        Caption = '60Hz'
        TabOrder = 1
        OnClick = rb_In_50Click
      end
      object rb_In_24: TRadioButton
        Tag = 2
        Left = 8
        Top = 48
        Width = 65
        Height = 17
        Caption = '24Hz'
        TabOrder = 2
        OnClick = rb_In_50Click
      end
      object rb_In_25: TRadioButton
        Tag = 3
        Left = 8
        Top = 64
        Width = 65
        Height = 17
        Caption = '25Hz'
        TabOrder = 3
        OnClick = rb_In_50Click
      end
      object rb_In_48: TRadioButton
        Tag = 4
        Left = 9
        Top = 80
        Width = 65
        Height = 17
        Caption = '48Hz'
        TabOrder = 4
        OnClick = rb_In_50Click
      end
      object rb_In_100: TRadioButton
        Tag = 5
        Left = 9
        Top = 96
        Width = 65
        Height = 17
        Caption = '100Hz'
        TabOrder = 5
        OnClick = rb_In_50Click
      end
      object rb_In_120: TRadioButton
        Tag = 6
        Left = 9
        Top = 112
        Width = 65
        Height = 17
        Caption = '120Hz'
        TabOrder = 6
        OnClick = rb_In_50Click
      end
      object rb_In_30: TRadioButton
        Tag = 7
        Left = 9
        Top = 128
        Width = 65
        Height = 17
        Caption = '30Hz'
        TabOrder = 7
        OnClick = rb_In_50Click
      end
    end
    object GroupBox13: TGroupBox
      Left = 170
      Top = 232
      Width = 167
      Height = 201
      Caption = 'Output VSync'
      TabOrder = 7
      object rb_Out_50: TRadioButton
        Left = 8
        Top = 16
        Width = 65
        Height = 17
        Caption = '50Hz'
        Checked = True
        TabOrder = 0
        TabStop = True
        OnClick = rb_Out_240Click
      end
      object rb_Out_100: TRadioButton
        Tag = 1
        Left = 8
        Top = 32
        Width = 65
        Height = 17
        Caption = '100Hz'
        TabOrder = 1
        OnClick = rb_Out_240Click
      end
      object rb_Out_200: TRadioButton
        Tag = 2
        Left = 8
        Top = 48
        Width = 65
        Height = 17
        Caption = '200Hz'
        TabOrder = 2
        OnClick = rb_Out_240Click
      end
      object rb_Out_60: TRadioButton
        Tag = 3
        Left = 8
        Top = 64
        Width = 65
        Height = 17
        Caption = '60Hz'
        TabOrder = 3
        OnClick = rb_Out_240Click
      end
      object rb_Out_120: TRadioButton
        Tag = 4
        Left = 8
        Top = 80
        Width = 65
        Height = 17
        Caption = '120Hz'
        TabOrder = 4
        OnClick = rb_Out_240Click
      end
      object rb_Out_240: TRadioButton
        Tag = 5
        Left = 8
        Top = 96
        Width = 65
        Height = 17
        Caption = '240Hz'
        TabOrder = 5
        OnClick = rb_Out_240Click
      end
      object rb_Out_75: TRadioButton
        Tag = 6
        Left = 8
        Top = 112
        Width = 65
        Height = 17
        Caption = '75Hz'
        TabOrder = 6
        OnClick = rb_Out_240Click
      end
    end
    object GroupBox14: TGroupBox
      Left = 226
      Top = 104
      Width = 271
      Height = 70
      Caption = 'Input Resolution'
      TabOrder = 8
      object RadioButton20: TRadioButton
        Left = 16
        Top = 24
        Width = 65
        Height = 17
        Caption = '1366'
        TabOrder = 0
        OnClick = RadioButton20Click
      end
      object RadioButton21: TRadioButton
        Tag = 1
        Left = 88
        Top = 24
        Width = 65
        Height = 17
        Caption = '1920'
        Checked = True
        Enabled = False
        TabOrder = 1
        TabStop = True
        OnClick = RadioButton20Click
      end
      object RadioButton32: TRadioButton
        Tag = 2
        Left = 160
        Top = 24
        Width = 65
        Height = 17
        Caption = '1280*720'
        TabOrder = 2
        OnClick = RadioButton20Click
      end
    end
    object GB_ReadBack: TGroupBox
      Left = 499
      Top = 232
      Width = 286
      Height = 201
      Caption = 'Read Back'
      TabOrder = 9
      object RegLabeledEdit1: TRegLabeledEdit
        Left = 185
        Top = 31
        Width = 77
        Height = 21
        EditLabel.Width = 61
        EditLabel.Height = 13
        EditLabel.Caption = 'Input V Total'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 0
        Visible = False
        RegStartAddress = '0xE000013A'
        RegBits = 11
        TextType = ttInt
      end
      object RegLabeledEdit2: TRegLabeledEdit
        Left = 97
        Top = 72
        Width = 77
        Height = 21
        EditLabel.Width = 62
        EditLabel.Height = 13
        EditLabel.Caption = 'Input H Total'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 1
        Visible = False
        RegStartAddress = '0xE0000135'
        RegBits = 11
        TextType = ttInt
      end
      object RegLabeledEdit3: TRegLabeledEdit
        Left = 16
        Top = 72
        Width = 77
        Height = 21
        EditLabel.Width = 69
        EditLabel.Height = 13
        EditLabel.Caption = 'Output V Total'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 2
        Visible = False
        RegStartAddress = '0xE000008C'
        RegBits = 12
        TextType = ttInt
      end
      object RegLabeledEdit4: TRegLabeledEdit
        Left = 177
        Top = 72
        Width = 85
        Height = 21
        EditLabel.Width = 70
        EditLabel.Height = 13
        EditLabel.Caption = 'Output H Total'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 3
        Visible = False
        RegStartAddress = '0xE000006C'
        RegBits = 12
        TextType = ttInt
      end
      object rle_Frame: TRegLabeledEdit
        Left = 94
        Top = 32
        Width = 76
        Height = 21
        EditLabel.Width = 85
        EditLabel.Height = 13
        EditLabel.Caption = 'Input Frame Cycle'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 4
        Visible = False
        RegStartAddress = '0xE00000C1'
        RegBits = 24
        TextType = ttInt
      end
      object rle_N: TRegLabeledEdit
        Left = 16
        Top = 32
        Width = 97
        Height = 21
        EditLabel.Width = 8
        EditLabel.Height = 13
        EditLabel.Caption = 'N'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 5
        RegStartAddress = '0xE0000069'
        RegBits = 8
        TextType = ttInt
      end
      object rle_M: TRegLabeledEdit
        Left = 138
        Top = 32
        Width = 119
        Height = 21
        EditLabel.Width = 9
        EditLabel.Height = 13
        EditLabel.Caption = 'M'
        LabelPosition = lpAbove
        LabelSpacing = 3
        TabOrder = 6
        RegStartAddress = '0xE00000D5'
        RegBits = 8
        TextType = ttInt
      end
      object rle_VSync: TLabeledEdit
        Left = 16
        Top = 72
        Width = 100
        Height = 21
        EditLabel.Width = 87
        EditLabel.Height = 13
        EditLabel.Caption = 'Input V Freuqency'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 7
      end
      object le_Clk: TLabeledEdit
        Left = 152
        Top = 112
        Width = 78
        Height = 21
        EditLabel.Width = 67
        EditLabel.Height = 13
        EditLabel.Caption = 'MC CLK(MHz)'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 8
        Text = '75'
      end
      object rle_ovsync: TLabeledEdit
        Left = 137
        Top = 72
        Width = 120
        Height = 21
        EditLabel.Width = 95
        EditLabel.Height = 13
        EditLabel.Caption = 'Output V Freuqency'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 9
      end
      object le_FilmMode: TLabeledEdit
        Left = 17
        Top = 116
        Width = 120
        Height = 21
        EditLabel.Width = 48
        EditLabel.Height = 13
        EditLabel.Caption = 'Film Mode'
        LabelPosition = lpAbove
        LabelSpacing = 3
        ReadOnly = True
        TabOrder = 10
      end
    end
    object GroupBox16: TGroupBox
      Left = 338
      Top = 232
      Width = 159
      Height = 201
      Caption = 'Film Mode'
      TabOrder = 10
      object rb_22: TRadioButton
        Tag = 1
        Left = 8
        Top = 32
        Width = 65
        Height = 17
        Caption = '22'
        TabOrder = 0
        OnClick = rb_videoClick
      end
      object rb_32: TRadioButton
        Tag = 2
        Left = 8
        Top = 48
        Width = 65
        Height = 17
        Caption = '32'
        TabOrder = 1
        OnClick = rb_videoClick
      end
      object rb_3223: TRadioButton
        Tag = 3
        Left = 8
        Top = 64
        Width = 65
        Height = 17
        Caption = '3223'
        TabOrder = 2
        OnClick = rb_videoClick
      end
      object rb_32322: TRadioButton
        Tag = 5
        Left = 8
        Top = 96
        Width = 65
        Height = 17
        Caption = '32322'
        TabOrder = 3
        OnClick = rb_videoClick
      end
      object rb_55: TRadioButton
        Tag = 7
        Left = 8
        Top = 128
        Width = 65
        Height = 17
        Caption = '55'
        TabOrder = 4
        OnClick = rb_videoClick
      end
      object rb_64: TRadioButton
        Tag = 8
        Left = 8
        Top = 144
        Width = 65
        Height = 17
        Caption = '64'
        TabOrder = 5
        OnClick = rb_videoClick
      end
      object rb_87: TRadioButton
        Tag = 9
        Left = 8
        Top = 160
        Width = 65
        Height = 17
        Caption = '87'
        TabOrder = 6
        OnClick = rb_videoClick
      end
      object rb_1123: TRadioButton
        Tag = 6
        Left = 8
        Top = 112
        Width = 65
        Height = 17
        Caption = '1123'
        TabOrder = 7
        OnClick = rb_videoClick
      end
      object rb_video: TRadioButton
        Left = 8
        Top = 15
        Width = 65
        Height = 17
        Caption = 'video'
        Checked = True
        TabOrder = 8
        TabStop = True
        OnClick = rb_videoClick
      end
      object rb_2224: TRadioButton
        Tag = 4
        Left = 8
        Top = 80
        Width = 65
        Height = 17
        Caption = '2224'
        TabOrder = 9
        OnClick = rb_videoClick
      end
      object rb_22_local: TRadioButton
        Tag = 10
        Left = 40
        Top = 32
        Width = 60
        Height = 17
        Caption = 'Local 22'
        TabOrder = 10
        OnClick = rb_videoClick
      end
      object rb_32_local: TRadioButton
        Tag = 11
        Left = 40
        Top = 48
        Width = 60
        Height = 17
        Caption = 'Local 32'
        TabOrder = 11
        OnClick = rb_videoClick
      end
    end
    object GB_Scalar: TGroupBox
      Left = 0
      Top = 56
      Width = 185
      Height = 49
      Caption = 'Scalar'
      TabOrder = 11
      object RegCheckBox1: TRegCheckBox
        Left = 16
        Top = 24
        Width = 97
        Height = 17
        Caption = 'VScalar 1.5x'
        TabOrder = 0
        RegAddress = '0xE0001001'
      end
    end
    object GroupBox15: TGroupBox
      Left = 497
      Top = 104
      Width = 288
      Height = 128
      Caption = 'L/R'
      TabOrder = 12
      object RegCheckBox2: TRegCheckBox
        Left = 24
        Top = 16
        Width = 137
        Height = 17
        Caption = 'Active Panel Left Image'
        TabOrder = 0
        RegAddress = '0xE0000309'
        RegBit = 6
      end
      object RegCheckBox3: TRegCheckBox
        Left = 24
        Top = 32
        Width = 145
        Height = 17
        Caption = 'Active Panel Right image'
        TabOrder = 1
        RegAddress = '0xE0000309'
        RegBit = 7
      end
      object RegCheckBox4: TRegCheckBox
        Left = 24
        Top = 48
        Width = 145
        Height = 17
        Caption = 'Passive Panel Left Image'
        TabOrder = 2
        RegAddress = '0xE0001301'
        RegBit = 3
      end
      object RegCheckBox5: TRegCheckBox
        Left = 24
        Top = 64
        Width = 145
        Height = 17
        Caption = 'Passive Panel Right image'
        TabOrder = 3
        RegAddress = '0xE0001301'
        RegBit = 2
      end
      object RegCheckBox6: TRegCheckBox
        Left = 24
        Top = 80
        Width = 145
        Height = 17
        Caption = 'Passive Panel Left Image'
        TabOrder = 4
        RegAddress = '0xE0001305'
        RegBit = 1
      end
      object RegCheckBox7: TRegCheckBox
        Left = 24
        Top = 96
        Width = 145
        Height = 17
        Caption = 'Passive Panel Right image'
        TabOrder = 5
        RegAddress = '0xE0001305'
      end
    end
    object btnTest: TButton
      Left = 24
      Top = 144
      Width = 129
      Height = 25
      Caption = 'test PC/VD 1000'
      TabOrder = 13
      OnClick = btnTestClick
    end
  end
end
