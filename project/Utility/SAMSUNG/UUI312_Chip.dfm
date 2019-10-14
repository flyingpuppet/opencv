inherited Form_UI312_Chip: TForm_UI312_Chip
  Left = 272
  Top = 106
  Width = 801
  Height = 687
  Caption = 'UI'
  OldCreateOrder = True
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object rg_Input_Format: TRadioGroup
    Left = 8
    Top = 88
    Width = 129
    Height = 105
    Caption = 'Input Format'
    ItemIndex = 0
    Items.Strings = (
      'Input_2D'
      'Input_3D_L/R'
      'Input_3D_TB'
      'Input_3D_SBS')
    TabOrder = 0
    OnClick = rg_Input_FormatClick
  end
  object rg_Output_Format: TRadioGroup
    Left = 136
    Top = 88
    Width = 129
    Height = 105
    Caption = 'Output Format'
    ItemIndex = 0
    Items.Strings = (
      'Output_2D'
      'Output_3D_PR'
      'Output_3D_SG'
      'Output_3D_SG_SS')
    TabOrder = 1
    OnClick = rg_Output_FormatClick
  end
  object rg_Input_Mode: TRadioGroup
    Left = 8
    Top = 48
    Width = 257
    Height = 41
    Caption = 'Input Mode'
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      'VD'
      'PC')
    TabOrder = 2
    OnClick = rg_Input_ModeClick
  end
  object rg_SwapLR: TRadioGroup
    Left = 8
    Top = 192
    Width = 257
    Height = 41
    Caption = 'Swap LR'
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      'L_To_R'
      'R_To_L')
    TabOrder = 3
    OnClick = rg_SwapLRClick
  end
  object gb_depth: TGroupBox
    Left = 8
    Top = 232
    Width = 257
    Height = 113
    Caption = '2D To 3D'
    TabOrder = 4
    object Label1: TLabel
      Left = 24
      Top = 20
      Width = 73
      Height = 13
      AutoSize = False
      Caption = 'Depth Level'
    end
    object Label2: TLabel
      Left = 24
      Top = 68
      Width = 73
      Height = 13
      AutoSize = False
      Caption = 'Disparity Level'
    end
    object tb_Depth: TTrackBar
      Left = 99
      Top = 16
      Width = 150
      Height = 45
      Orientation = trHorizontal
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 0
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = tb_DepthChange
    end
    object tb_Disparity: TTrackBar
      Left = 99
      Top = 64
      Width = 150
      Height = 45
      Orientation = trHorizontal
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = tb_DisparityChange
    end
  end
  object Button1: TButton
    Left = 8
    Top = 616
    Width = 75
    Height = 25
    Caption = 'Refresh'
    TabOrder = 5
    OnClick = Button1Click
  end
  object GroupBox2: TGroupBox
    Left = 272
    Top = 48
    Width = 209
    Height = 105
    Caption = 'PWM 2D'
    TabOrder = 6
    object rle_PWM_Freq: TRegLabeledEdit
      Left = 80
      Top = 32
      Width = 121
      Height = 21
      EditLabel.Width = 57
      EditLabel.Height = 13
      EditLabel.Caption = 'PWM Freq: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 0
      RegStartAddress = '0x9F020055'
      RegBits = 8
      MailBox_Address = '0xC00A00A0'
    end
    object rle_PWM_Duty: TRegLabeledEdit
      Left = 80
      Top = 72
      Width = 121
      Height = 21
      EditLabel.Width = 58
      EditLabel.Height = 13
      EditLabel.Caption = 'PWM Duty: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 1
      RegStartAddress = '0x9F020056'
      RegBits = 16
      MailBox_Address = '0xC00A00A0'
    end
  end
  object rle_Test_Pattern: TRegLabeledEdit
    Left = 640
    Top = 8
    Width = 46
    Height = 21
    EditLabel.Width = 64
    EditLabel.Height = 13
    EditLabel.Caption = 'Test Pattern: '
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 7
    RegStartAddress = '0x9F020054'
    RegBits = 8
    MailBox_Address = '0xC00A00A0'
  end
  object GroupBox3: TGroupBox
    Left = 272
    Top = 248
    Width = 209
    Height = 97
    Caption = 'Blue Tooth Sync'
    TabOrder = 8
    object rle_BT_Delay: TRegLabeledEdit
      Left = 80
      Top = 32
      Width = 121
      Height = 21
      EditLabel.Width = 36
      EditLabel.Height = 13
      EditLabel.Caption = 'Delay : '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 0
      RegStartAddress = '0x9F02005C'
      RegBits = 16
      MailBox_Address = '0xC00A00A0'
    end
    object rle_BT_Duty: TRegLabeledEdit
      Left = 80
      Top = 64
      Width = 121
      Height = 21
      EditLabel.Width = 31
      EditLabel.Height = 13
      EditLabel.Caption = 'Duty : '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 1
      RegStartAddress = '0x9F020058'
      RegBits = 16
      MailBox_Address = '0xC00A00A0'
    end
  end
  object GroupBox4: TGroupBox
    Left = 272
    Top = 152
    Width = 209
    Height = 89
    Caption = '3D PWM Dimming'
    TabOrder = 9
    object rle_3DPWM_Delay: TRegLabeledEdit
      Left = 80
      Top = 24
      Width = 121
      Height = 21
      EditLabel.Width = 36
      EditLabel.Height = 13
      EditLabel.Caption = 'Delay : '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 0
      RegStartAddress = '0x9F020068'
      RegBits = 16
      MailBox_Address = '0xC00A00A0'
    end
    object rle_3DPWM_Duty: TRegLabeledEdit
      Left = 80
      Top = 56
      Width = 121
      Height = 21
      EditLabel.Width = 31
      EditLabel.Height = 13
      EditLabel.Caption = 'Duty : '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 1
      RegStartAddress = '0x9F02006A'
      RegBits = 16
      MailBox_Address = '0xC00A00A0'
    end
  end
  object rg_OutFre: TRadioGroup
    Left = 8
    Top = 352
    Width = 473
    Height = 41
    Caption = 'Output Frequency'
    Columns = 3
    ItemIndex = 0
    Items.Strings = (
      '50->100'
      '60->120'
      '50->120')
    TabOrder = 10
    OnClick = rg_OutFreClick
  end
  object rcb_panel: TRegCheckBox
    Tag = 1
    Left = 16
    Top = 16
    Width = 113
    Height = 17
    Caption = 'non-Inverse Panel'
    TabOrder = 11
    RegAddress = '0xE0000FA8'
    RegBit = 1
  end
  object rcb_bbPanel: TRegCheckBox
    Tag = 1
    Left = 152
    Top = 16
    Width = 73
    Height = 17
    Caption = 'BB Panel'
    TabOrder = 12
    RegAddress = '0xE0000FA8'
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 400
    Width = 473
    Height = 209
    Caption = 'FRC'
    TabOrder = 13
    object Label3: TLabel
      Left = 16
      Top = 105
      Width = 73
      Height = 13
      AutoSize = False
      Caption = 'FRC Level'
    end
    object Label4: TLabel
      Left = 16
      Top = 148
      Width = 81
      Height = 13
      AutoSize = False
      Caption = 'DeJudder Level'
    end
    object tb_FRC: TTrackBar
      Left = 96
      Top = 96
      Width = 369
      Height = 45
      Orientation = trHorizontal
      PageSize = 1
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 0
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = tb_FRCChange
    end
    object tb_Dejudder: TTrackBar
      Left = 96
      Top = 144
      Width = 369
      Height = 45
      Orientation = trHorizontal
      PageSize = 1
      Frequency = 1
      Position = 0
      SelEnd = 0
      SelStart = 0
      TabOrder = 1
      TickMarks = tmBottomRight
      TickStyle = tsAuto
      OnChange = tb_DejudderChange
    end
    object rg_frc: TRadioGroup
      Left = 16
      Top = 32
      Width = 449
      Height = 41
      Columns = 6
      ItemIndex = 1
      Items.Strings = (
        'Off'
        'standard'
        'smooth'
        'clear'
        'custom'
        'demo')
      TabOrder = 2
      OnClick = rg_frcClick
    end
  end
  object rg_Mailbox: TRadioGroup
    Left = 488
    Top = 48
    Width = 297
    Height = 113
    Caption = 'Mailbox protocol'
    ItemIndex = 2
    Items.Strings = (
      'None'
      'Only address'
      'Addr & Bit')
    TabOrder = 14
    OnClick = rg_MailboxClick
  end
  object rle_Mute: TRegLabeledEdit
    Left = 520
    Top = 8
    Width = 50
    Height = 21
    EditLabel.Width = 60
    EditLabel.Height = 13
    EditLabel.Caption = 'Video Mute: '
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 15
    RegStartAddress = '0x9F02004C'
    RegBits = 4
    RegStart = 16
    MailBox_Address = '0xC00A00A0'
  end
  object RegLabeledEdit10: TRegLabeledEdit
    Left = 400
    Top = 8
    Width = 49
    Height = 21
    EditLabel.Width = 68
    EditLabel.Height = 13
    EditLabel.Caption = 'DEMO Enable'
    LabelPosition = lpLeft
    LabelSpacing = 3
    TabOrder = 16
    RegStartAddress = '0x9F020040'
    RegBits = 2
    RegStart = 8
    MailBox_Address = '0xC00A00A0'
  end
  object gb_WB: TGroupBox
    Left = 489
    Top = 166
    Width = 296
    Height = 441
    Caption = 'White Balance'
    TabOrder = 17
    object RegLabeledEdit1: TRegLabeledEdit
      Left = 72
      Top = 64
      Width = 53
      Height = 21
      EditLabel.Width = 39
      EditLabel.Height = 13
      EditLabel.Caption = 'R Gain: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 0
      OnExit = RegEditExit
      OnKeyPress = RegEditKeyPress
      RegStartAddress = '0x9F02006C'
      RegBits = 10
      TextType = ttInt
      MailBox_Address = '0xC00A00A0'
    end
    object RegLabeledEdit2: TRegLabeledEdit
      Left = 72
      Top = 106
      Width = 53
      Height = 21
      EditLabel.Width = 39
      EditLabel.Height = 13
      EditLabel.Caption = 'G Gain: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 1
      OnExit = RegEditExit
      OnKeyPress = RegEditKeyPress
      RegStartAddress = '0x9F02006C'
      RegBits = 10
      RegStart = 10
      TextType = ttInt
      MailBox_Address = '0xC00A00A0'
    end
    object RegLabeledEdit3: TRegLabeledEdit
      Left = 72
      Top = 148
      Width = 53
      Height = 21
      EditLabel.Width = 38
      EditLabel.Height = 13
      EditLabel.Caption = 'B Gain: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 2
      OnExit = RegEditExit
      OnKeyPress = RegEditKeyPress
      RegStartAddress = '0x9F02006C'
      RegBits = 10
      RegStart = 20
      TextType = ttInt
      MailBox_Address = '0xC00A00A0'
    end
    object RegLabeledEdit4: TRegLabeledEdit
      Left = 72
      Top = 190
      Width = 53
      Height = 21
      EditLabel.Width = 58
      EditLabel.Height = 13
      EditLabel.Caption = 'R OFFSET: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 3
      OnExit = RegEditExit
      OnKeyPress = RegEditKeyPress
      RegStartAddress = '0x9F020070'
      RegBits = 10
      TextType = ttInt
      MailBox_Address = '0xC00A00A0'
    end
    object RegLabeledEdit5: TRegLabeledEdit
      Left = 72
      Top = 232
      Width = 53
      Height = 21
      EditLabel.Width = 58
      EditLabel.Height = 13
      EditLabel.Caption = 'G OFFSET: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 4
      OnExit = RegEditExit
      OnKeyPress = RegEditKeyPress
      RegStartAddress = '0x9F020070'
      RegBits = 10
      RegStart = 10
      TextType = ttInt
      MailBox_Address = '0xC00A00A0'
    end
    object RegLabeledEdit6: TRegLabeledEdit
      Left = 72
      Top = 274
      Width = 53
      Height = 21
      EditLabel.Width = 57
      EditLabel.Height = 13
      EditLabel.Caption = 'B OFFSET: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 5
      OnExit = RegEditExit
      OnKeyPress = RegEditKeyPress
      RegStartAddress = '0x9F020070'
      RegBits = 10
      RegStart = 20
      TextType = ttInt
      MailBox_Address = '0xC00A00A0'
    end
    object RegLabeledEdit7: TRegLabeledEdit
      Left = 72
      Top = 316
      Width = 53
      Height = 21
      EditLabel.Width = 45
      EditLabel.Height = 13
      EditLabel.Caption = 'R LIMIT: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 6
      OnExit = RegEditExit
      OnKeyPress = RegEditKeyPress
      RegStartAddress = '0x9F020078'
      RegBits = 10
      TextType = ttInt
      MailBox_Address = '0xC00A00A0'
    end
    object RegLabeledEdit8: TRegLabeledEdit
      Left = 72
      Top = 358
      Width = 53
      Height = 21
      EditLabel.Width = 45
      EditLabel.Height = 13
      EditLabel.Caption = 'G LIMIT: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 7
      OnExit = RegEditExit
      OnKeyPress = RegEditKeyPress
      RegStartAddress = '0x9F020078'
      RegBits = 10
      RegStart = 10
      TextType = ttInt
      MailBox_Address = '0xC00A00A0'
    end
    object RegLabeledEdit9: TRegLabeledEdit
      Left = 72
      Top = 400
      Width = 53
      Height = 21
      EditLabel.Width = 44
      EditLabel.Height = 13
      EditLabel.Caption = 'B LIMIT: '
      LabelPosition = lpLeft
      LabelSpacing = 3
      TabOrder = 8
      OnExit = RegEditExit
      OnKeyPress = RegEditKeyPress
      RegStartAddress = '0x9F020078'
      RegBits = 10
      RegStart = 20
      TextType = ttInt
      MailBox_Address = '0xC00A00A0'
    end
    object RegCheckBox1: TRegCheckBox
      Left = 32
      Top = 32
      Width = 153
      Height = 17
      Caption = 'White Banlance Enable'
      TabOrder = 9
      RegAddress = '0x9F020040'
      RegBit = 2
      MailBox_Address = '0xC00A00A0'
    end
    object RegScrollBar_RGain: TRegScrollBar
      Left = 140
      Top = 67
      Width = 137
      Height = 17
      Max = 1023
      PageSize = 0
      TabOrder = 10
      OnScroll = RegScrollBarScroll
      RegStartAddress = '0x9F02006C'
      RegBits = 10
      MailBox_Address = '0xC00A00A0'
    end
    object RegScrollBar_GGain: TRegScrollBar
      Left = 140
      Top = 108
      Width = 137
      Height = 17
      Max = 1023
      PageSize = 0
      TabOrder = 11
      OnScroll = RegScrollBarScroll
      RegStartAddress = '0x9F02006C'
      RegBits = 10
      RegStart = 10
      MailBox_Address = '0xC00A00A0'
    end
    object RegScrollBar_BGain: TRegScrollBar
      Left = 140
      Top = 150
      Width = 137
      Height = 17
      Max = 1023
      PageSize = 0
      TabOrder = 12
      OnScroll = RegScrollBarScroll
      RegStartAddress = '0x9F02006C'
      RegBits = 10
      RegStart = 20
      MailBox_Address = '0xC00A00A0'
    end
    object RegScrollBar_ROff: TRegScrollBar
      Left = 140
      Top = 191
      Width = 137
      Height = 17
      Max = 1023
      PageSize = 0
      TabOrder = 13
      OnScroll = RegScrollBarScroll
      RegStartAddress = '0x9F020070'
      RegBits = 10
      MailBox_Address = '0xC00A00A0'
    end
    object RegScrollBar_GOff: TRegScrollBar
      Left = 140
      Top = 234
      Width = 137
      Height = 17
      Max = 1023
      PageSize = 0
      TabOrder = 14
      OnScroll = RegScrollBarScroll
      RegStartAddress = '0x9F020070'
      RegBits = 10
      RegStart = 10
      MailBox_Address = '0xC00A00A0'
    end
    object RegScrollBar_BOff: TRegScrollBar
      Left = 140
      Top = 276
      Width = 137
      Height = 17
      Max = 1023
      PageSize = 0
      TabOrder = 15
      OnScroll = RegScrollBarScroll
      RegStartAddress = '0x9F020070'
      RegBits = 10
      RegStart = 20
      MailBox_Address = '0xC00A00A0'
    end
    object RegScrollBar_RLmt: TRegScrollBar
      Left = 140
      Top = 318
      Width = 137
      Height = 17
      Max = 1023
      PageSize = 0
      TabOrder = 16
      OnScroll = RegScrollBarScroll
      RegStartAddress = '0x9F020078'
      RegBits = 10
      MailBox_Address = '0xC00A00A0'
    end
    object RegScrollBar_GLmt: TRegScrollBar
      Left = 140
      Top = 360
      Width = 137
      Height = 17
      Max = 1023
      PageSize = 0
      TabOrder = 17
      OnScroll = RegScrollBarScroll
      RegStartAddress = '0x9F020078'
      RegBits = 10
      RegStart = 10
      MailBox_Address = '0xC00A00A0'
    end
    object RegScrollBar_BLmt: TRegScrollBar
      Left = 140
      Top = 401
      Width = 137
      Height = 17
      Max = 1023
      PageSize = 0
      TabOrder = 18
      OnScroll = RegScrollBarScroll
      RegStartAddress = '0x9F020078'
      RegBits = 10
      RegStart = 20
      MailBox_Address = '0xC00A00A0'
    end
  end
  object RegScrollBar1: TRegScrollBar
    Left = 592
    Top = 72
    Width = 121
    Height = 17
    PageSize = 0
    TabOrder = 18
  end
  object RegCheckBox2: TRegCheckBox
    Left = 616
    Top = 104
    Width = 97
    Height = 17
    Caption = 'Freerun'
    TabOrder = 19
    RegAddress = '0x9F020041'
    RegBit = 3
    MailBox_Address = '0xC00A00A0'
  end
end